import time
from pyspark.sql import SQLContext
from pyspark import SparkContext
# 利用spark的csv库直接载入csv格式的数据
sc = SparkContext()
sqlContext = SQLContext(sc)
data = sqlContext.read.format('com.databricks.spark.csv').options(header='true',
                                                                  inferschema='true').load('train1.csv')
# 选10000条数据集，减少运行时间
data = data.sample(False,0.01, 100)
print(data.count())
drop_list = ['Descript']
data = data.select([column for column in data.columns if column not in drop_list])
data.show(5)
data.printSchema()
from pyspark.sql.functions import col
data.groupBy('Category').count().orderBy(col('count').desc()).show()
from pyspark.ml.feature import RegexTokenizer, StopWordsRemover, CountVectorizer
from pyspark.ml.classification import LogisticRegression
# 正则切分单词
# inputCol:输入字段名
# outputCol:输出字段名
regexTokenizer = RegexTokenizer(inputCol='Title', outputCol='words', pattern='\\W')
# 停用词
add_stopwords = ['http', 'https', 'amp', 'rt', 't', 'c', 'the']
stopwords_remover = StopWordsRemover(inputCol='words', outputCol='filtered').setStopWords(add_stopwords)
# 构建词频向量
count_vectors = CountVectorizer(inputCol='filtered', outputCol='features', vocabSize=20000, minDF=3)
from pyspark.ml import Pipeline
from pyspark.ml.feature import OneHotEncoder, StringIndexer, VectorAssembler
label_stringIdx = StringIndexer(inputCol='Category', outputCol='label')
pipeline = Pipeline(stages=[regexTokenizer, stopwords_remover, count_vectors, label_stringIdx])
# fit the pipeline to training documents
pipeline_fit = pipeline.fit(data)
dataset = pipeline_fit.transform(data)
dataset.show(20)
(trainingData, testData) = dataset.randomSplit([0.7, 0.3], seed=100)
print('Training Dataset Count:{}'.format(trainingData.count()))
print('Test Dataset Count:{}'.format(testData.count()))
from pyspark.ml.feature import HashingTF, IDF
start_time = time.time()
# numFeatures: 最大特征数
hashingTF = HashingTF(inputCol='filtered', outputCol='rawFeatures', numFeatures=10000)
# minDocFreq：过滤的最少文档数量
idf = IDF(inputCol='rawFeatures', outputCol='features', minDocFreq=5)
pipeline = Pipeline(stages=[regexTokenizer, stopwords_remover, hashingTF, idf, label_stringIdx])
pipeline_fit = pipeline.fit(data)
dataset = pipeline_fit.transform(data)
(trainingData, testData) = dataset.randomSplit([0.7, 0.3], seed=100)

lr = LogisticRegression(maxIter=20, regParam=0.3, elasticNetParam=0)
lr_model = lr.fit(trainingData)
predictions = lr_model.transform(testData)
predictions.filter(predictions['prediction'] == 0).select('Title', 'Category', 'probability', 'label', 'prediction').\
orderBy('probability', ascending=False).show(n=10, truncate=30)
from pyspark.ml.evaluation import MulticlassClassificationEvaluator
# predictionCol: 预测列的名称
evaluator = MulticlassClassificationEvaluator(predictionCol='prediction')
evaluator_acc = MulticlassClassificationEvaluator(predictionCol="prediction", metricName="accuracy")
evaluator_f1 = MulticlassClassificationEvaluator(predictionCol="prediction", metricName="f1")
evaluator_pre = MulticlassClassificationEvaluator(predictionCol="prediction", metricName="weightedPrecision")
evaluator_recall = MulticlassClassificationEvaluator(predictionCol="prediction", metricName="weightedRecall")

# 预测准确率
print(evaluator.evaluate(predictions))
print('pyspark accuracy: %.6f' %evaluator_acc.evaluate(predictions))
print('pyspark f1-score: %.6f' %evaluator_f1.evaluate(predictions))
print('pyspark precision: %.6f' %evaluator_pre.evaluate(predictions))
print('pyspark recall: %.6f' %evaluator_recall.evaluate(predictions))

end_time = time.time()
print(end_time - start_time)