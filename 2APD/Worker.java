import java.util.Map.Entry;
import java.util.TreeMap;

/*
 * Clasa ce reprezinta un thread worker.
 */
class Worker extends Thread {
	WorkPool wp;
	Main m;
	boolean gata;
	

	public Worker(WorkPool workpool, Main main) {
		this.wp = workpool;
		this.m = main;
		this.gata = false;
	}
	
	/*
	 * Procesarea unei solutii partiale. Aceasta poate implica generarea unor
	 * noi solutii partiale care se adauga in workpool folosind putWork().
	 * Daca s-a ajuns la o solutie finala, aceasta va fi afisata.
	 */
	void processPartialSolution(PartialSolution ps) {
		if (ps.a == true)
		{
			//map
			
			/*
			 * Calcularea nr de aparitii
			 */
			String s = ps.sir.replaceAll("-|\\.|\\,|\\(|\\)|0|1|2|3|4|5|6|7|8|9|0|\"|\'", " ");
			String[] sect = s.split("([\\W\\s]+)");
		
			TreeMap<String, Double> parttree = new TreeMap<String, Double>();
			for(String iterator : sect) {
				if(!parttree.containsKey(iterator)) {
					parttree.put(iterator, 1.0);
				} else {
					parttree.put(iterator, parttree.get(iterator) + 1);
				}
			}
			
			m.rezultat.get(ps.fis).add(parttree);
			
		} else {
			//reduce
			
			/*
			 * Agregarea vectorului de vector partiali intr-unul singur, final
			 */
			this.gata = false;
			
			TreeMap<String, Double> b = ps.sir2;
			
			for (Entry<String, Double> it : ps.sir1.entrySet())
			{
				if (b.containsKey(it.getKey()))
				{
					b.put(it.getKey(), it.getValue() + b.get(it.getKey()));
				} else {
					b.put(it.getKey(), it.getValue());
				}
			}
			synchronized(m) {
				m.rezultat.get(ps.fis).add(b);
				this.gata = true;
			}
		}
		
	}
	
	
	public void run() {
		//System.out.println("Thread-ul worker " + this.getName() + " a pornit...");
		while (true) {
			PartialSolution ps = wp.getWork();
			if (ps == null)
				break;
			
			processPartialSolution(ps);
		}
		//System.out.println("Thread-ul worker " + this.getName() + " s-a terminat...");
	}

	
}