import java.util.TreeMap;

/*
 * Clasa ce reprezinta o solutie partiala pentru problema de rezolvat. Aceste
 * solutii partiale constituie task-uri care sunt introduse in workpool.
 */
class PartialSolution {
	int fis;
	int poz_init;
	int poz_final;
	String sir;
	boolean a;
	TreeMap<String, Double> sir1;
	TreeMap<String, Double> sir2;
	
	public PartialSolution(int fis, int poz_init, int poz_final, String sir, boolean a, TreeMap<String, Double> sir1, TreeMap<String, Double> sir2)
	{
		this.fis = fis;
		this.poz_init = poz_init;
		this.poz_final = poz_final;
		this.sir = sir;
		this.a = a;
		this.sir1 = sir1;
		this.sir2 = sir2;
	}
	
}