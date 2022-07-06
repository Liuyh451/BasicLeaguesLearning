package java_4_5;

public class Machine {
		
		public void Checkbag(Goods goods) throws DangerException{
			if(goods.isDanger){
				throw new DangerException();
			}
			
		}

	}

