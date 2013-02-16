/*
 * Tema2 APD - Indexarea documentelor folosing paradigma Map-Reduce
 * Necula Roxana - Valentina 332CA
 */

import java.io.*;	
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.Vector;

public class Main
{
	public Integer nc;
	public Vector<String> v_nc;
	public Integer d;
	public Integer n;
	public Integer x;
	public Integer nd;
	public Vector<String> v_nd;
	public Vector<String> date_fisiere;
	public ArrayList<ArrayList<TreeMap<String, Double>>> rezultat;
	public ArrayList<TreeMap<String, Double>> vector_final;
	public ArrayList<TreeMap<String, Double>> vector_final_sortat;
	public ArrayList<TreeMap<String, Double>> final_final;
	public ArrayList<TreeMap<String, Double>> final_final_sortat;
	
	Main()
	{
		this.nc = new Integer("0");
		this.v_nc = new Vector<String>();
		this.d = new Integer("0");
		this.n = new Integer("0");
		this.x = new Integer("0");
		this.nd = new Integer("0");
		this.v_nd = new Vector<String>();
		this.date_fisiere = new Vector<String>();
		this.rezultat = new ArrayList<ArrayList<TreeMap<String, Double>>>();
		this.vector_final = new ArrayList<TreeMap<String, Double>>();
		this.vector_final_sortat = new ArrayList<TreeMap<String, Double>>();
		this.final_final = new ArrayList<TreeMap<String, Double>>();
		this.final_final_sortat = new ArrayList<TreeMap<String, Double>>();
	}
	
	public void allocateVector()
	{
		for (int i = 0; i < nd; i++)
		{
			ArrayList<TreeMap<String, Double>> t = new ArrayList<TreeMap<String, Double>>();
			rezultat.add(t);
		}
	}
	
	/*
	 * Functie folosita pentru citirea din fisier
	 * - memorez fiecare fisier cu date intr-un vector de stringuri = this.date_fisiere
	 */
	void citeste(FileInputStream fstream) throws IOException
	{
		DataInputStream in = new DataInputStream(fstream);
		BufferedReader br = new BufferedReader(new InputStreamReader(in));
		String strLine;
		Vector<String> inp = new Vector<String>();
		while ((strLine = br.readLine()) != null)
		{
			inp.add(strLine);
		}
				
		nc = Integer.valueOf(inp.elementAt(0));			
	
		String vec_nc = new String();
		vec_nc = inp.elementAt(1);
		
		String[] vec2_nc;
		vec2_nc = vec_nc.split(" ");
		for (int i = 0; i < nc; i++)
			v_nc.add(vec2_nc[i]);			
							
		d = Integer.valueOf(inp.elementAt(2));
		
		n = Integer.valueOf(inp.elementAt(3));
		
		x = Integer.valueOf(inp.elementAt(4));
		
		nd = Integer.valueOf(inp.elementAt(5));
		
		for (int i = 0; i < nd; i++)
			v_nd.add(inp.elementAt(i + 6));
		
		in.close();
		
		Vector<FileInputStream> nd_stream = new Vector<FileInputStream>(nd);
		Vector<DataInputStream> nd_in = new Vector<DataInputStream>(nd);
		Vector<BufferedReader> nd_br = new Vector<BufferedReader>(nd);
		
		for (int i = 0; i < nd; i++)
		{
			FileInputStream fis_s = new FileInputStream(v_nd.elementAt(i));
			nd_stream.add(fis_s);
			DataInputStream fis_in = new DataInputStream(nd_stream.elementAt(i));
			nd_in.add(fis_in);
			BufferedReader fis_br = new BufferedReader(new InputStreamReader(nd_in.elementAt(i)));
			nd_br.add(fis_br);
		}
		
		String strLine2;
		for (int i = 0; i < nd; i++)
		{
			String s = new String();
			while ((strLine2 = nd_br.elementAt(i).readLine()) != null)
			{
				s = s + strLine2 + " ";
				s = s.toLowerCase();
			}
			String rep = s.replace("\n", " ");
			rep = s.replace("\t", " ");
			date_fisiere.add(rep);
		}
		
		for (int i = 0; i < nd; i++)
			nd_in.elementAt(i).close();
					
	}
	
	public static void main(String args[]) throws IOException, InterruptedException
	{
		FileInputStream fstream = new FileInputStream(args[1]);
		Main m = new Main();
		m.citeste(fstream);
		m.allocateVector();
		WorkPool wp_map = new WorkPool(100);
		
		/*
		 * Prelucrarea documentelor - trimit fiecare D octeti de date la prelucrat in WorkPool-ul wp_map
		 * - retin intr-un ArrayList<ArrayList<>> vectorii partiali
		 */
		for (int i = 0; i < m.nd; i++)
		{
			int pozI = 0;
			int pozF = m.d;
			if (Character.isLetter(m.date_fisiere.get(i).charAt(pozF)))
				while (Character.isLetter(m.date_fisiere.get(i).charAt(pozF)))
				{
					pozF++;
				}
			while (pozF < m.date_fisiere.get(i).length() && pozI != pozF)
			{
				String sir = m.date_fisiere.get(i).substring(pozI, pozF);
				PartialSolution p = new PartialSolution(i, pozI, pozF, sir, true, null, null);
				wp_map.putWork(p);
				pozI = Math.min(pozF + 1,m.date_fisiere.get(i).length() - 1);
				pozF = pozI + m.d;

				if (pozF < m.date_fisiere.get(i).length() && Character.isLetter(m.date_fisiere.get(i).charAt(pozF)))
				{
					while (Character.isLetter(m.date_fisiere.get(i).charAt(pozF)))
					{
						pozF++;
					}
				} 
					pozF = Math.min(m.date_fisiere.get(i).length() - 1,pozF);	
				
			}
		}
		
		Integer nt = Integer.parseInt(args[0]);
		ArrayList<Worker> w1 = new ArrayList<Worker>(nt);
		for (int i = 0; i < nt; i++)
		{
			Worker wi = new Worker(wp_map, m);
			w1.add(wi);
			w1.get(i).start();
		}
		
		while(wp_map.tasks.size() > 0 )
		{
			Thread.sleep(100);
		}
		
		for (int i = 0; i < m.nd; i++)
		{
			for (int j = 0; j < m.rezultat.get(i).size(); j++)
			{
				Set set = m.rezultat.get(i).get(j).entrySet();
				Iterator it = set.iterator();
				while (it.hasNext())
				{
					Map.Entry me = (Map.Entry)it.next();
				}
				
			}
		}
		
		/*
		 * WorkPool-ul wp_red se ocupa de calcularea nr de aparitii
		 * - iau fiecare 2 vectori partiali, le calculez nr aparitii si trec mai departe,
		 * pana cand raman cu un singur vector
		 */
		WorkPool wp_red = new WorkPool(100);
		ArrayList<Worker> w2 = new ArrayList<Worker>(nt);
		for (int i = 0; i < nt; i++)
		{
			Worker wi = new Worker(wp_red, m);
			w2.add(wi);
			w1.get(i).stop();
			w2.get(i).start();
		}
		for (int i = 0; i < m.nd; i++)
		{
			while(m.rezultat.get(i).size() > 1 ) {
				while(m.rezultat.get(i).size() > 1) {


					TreeMap<String, Double> f = m.rezultat.get(i).get(0);
					m.rezultat.get(i).remove(0);
					TreeMap<String, Double> s = m.rezultat.get(i).get(0);
					m.rezultat.get(i).remove(0);
					PartialSolution ps = new PartialSolution(i, 0, 0, null, false, f , s );
					wp_red.putWork(ps);
				}

				boolean term = false;
				while (wp_red.tasks.size() > 0 || ( wp_red.tasks.size() == 0 && term != true)) {
					term = true;
					if(wp_red.tasks.size() == 0)
						for (int j = 0; j < nt; j++)
						{
							if (w2.get(i).gata != true)
								term = false;
						}
						Thread.sleep(10);
				}

			}
		}
		for (int i = 0; i < nt; i++)
		{
			w2.get(i).stop();
		}
		
		/*
		 * Calculez nr total de aparitii pentru a calcula frecventa maxima
		 */
		ArrayList<Double> nr_total = new ArrayList<Double>();
		for (int i = 0; i < m.nd; i++)
			nr_total.add(0.0);
		for (int i = 0; i < m.nd; i++)
		{
			for (int j = 0; j < m.rezultat.get(i).size(); j++)
			{
				Set set = m.rezultat.get(i).get(j).entrySet();
				Iterator it = set.iterator();
				while (it.hasNext())
				{
					Map.Entry me = (Map.Entry)it.next();
					Double nr = (Double) me.getValue();
					nr = nr_total.get(i) + nr;
					nr_total.set(i, nr);
				}
				
			}
		}
		
		ArrayList<TreeMap<String, Double>> test = new ArrayList<TreeMap<String, Double>>();
		ArrayList<TreeMap<String, Double>> sorted_test = new ArrayList<TreeMap<String, Double>>();
		for (int i = 0; i < m.nd; i++)
		{
			TreeMap<String, Double> a = new TreeMap<String, Double>();
			test.add(a);
			sorted_test.add(a);
		}
		
		/*
		 * Vectorii test si sorted_test contin toate perechile de <String, Double> ce reprezinta <cuvant, nr de aparitii>
		 */
		for (int i = 0; i < m.nd; i++)
		{
			for (int j = 0; j < m.rezultat.get(i).size(); j++)
			{
				Set set = m.rezultat.get(i).get(j).entrySet();
				Iterator it = set.iterator();
				while (it.hasNext())
				{
					Map.Entry me = (Map.Entry)it.next();
					test.get(i).put((String)me.getKey(),(Double)me.getValue());
				}
			}
		}
		
		for (int i = 0; i < m.nd; i++)
		{
			ValueComparator bvc =  new ValueComparator(test.get(i));
			TreeMap<String, Double> sorted_map = new TreeMap<String,Double>(bvc);
			sorted_map.putAll(test.get(i));
			sorted_test.add(i, sorted_map);
		}
		ArrayList<ArrayList<String>> vs = new ArrayList<ArrayList<String>>();
		ArrayList<ArrayList<Double>> vn = new ArrayList<ArrayList<Double>>();
		for (int i = 0; i < m.nd; i++)
		{
			ArrayList<String> t = new ArrayList<String>();
			ArrayList<Double> tb = new ArrayList<Double>();
			vs.add(t);
			vn.add(tb);
		}
		
		for (int i = 0; i < m.nd; i++)
		{
			Set set = sorted_test.get(i).entrySet();
			Iterator it = set.iterator();
			while (it.hasNext())
			{
				Map.Entry me = (Map.Entry)it.next();
				vs.get(i).add((String)me.getKey());
				Double inm = ((Double)me.getValue() * 100) / nr_total.get(i);
				vn.get(i).add(Math.round(inm*100.0)/100.0);
			}
		}	

		/*
		 * Verific sa iau toate cuvintele care au aceeasi frecventa
		 */
		int abb = 0;
		ArrayList<Integer> adunat = new ArrayList<Integer>();
		for (int i = 0; i < m.nd; i++)
		{
			abb = 0;
			for (int k = m.n; k < vn.get(i).size(); k++)
				if (vn.get(i).get(m.n - 1).equals(vn.get(i).get(k)))
					abb++;
			adunat.add(i, abb);
		}
		
		
		for (int i = 0; i < m.nd; i++)
		{
			int j = 0;
			TreeMap<String, Double> fin = new TreeMap<String, Double>();
			TreeMap<String, Double> fin2 = new TreeMap<String, Double>();
			Set set = sorted_test.get(i).entrySet();
			Iterator it = set.iterator();
			while (it.hasNext() && j++ < m.n)
			{
				Map.Entry me = (Map.Entry)it.next();
				fin.put((String)me.getKey(),(Double)me.getValue());
				Double inm = ((Double)me.getValue() * 100) / nr_total.get(i);
				fin2.put((String)me.getKey(),Math.round(inm*100.0)/100.0);
				
			}
			m.vector_final.add(fin);
			m.final_final.add(fin2);
		}
		
		
		
		for (int i = 0; i < m.nd; i++)
		{
			ValueComparator bvc =  new ValueComparator(m.vector_final.get(i));
			TreeMap<String, Double> sorted_map = new TreeMap<String,Double>(bvc);
			sorted_map.putAll(m.vector_final.get(i));
			m.vector_final_sortat.add(i, sorted_map);
		}
		
		for (int i = 0; i < m.nd; i++)
		{
			ValueComparator bvc =  new ValueComparator(m.final_final.get(i));
			TreeMap<String, Double> sorted_map = new TreeMap<String,Double>(bvc);
			sorted_map.putAll(m.final_final.get(i));
			m.final_final_sortat.add(i, sorted_map);
		}		
		
		ArrayList<ArrayList<String>> cuv = new ArrayList<ArrayList<String>>();
		ArrayList<ArrayList<Double>> frecv = new ArrayList<ArrayList<Double>>();
		
		for (int i = 0; i < m.nd; i++)
		{
			ArrayList<String> t = new ArrayList<String>();
			cuv.add(t);
			ArrayList<Double> tz = new ArrayList<Double>();
			frecv.add(tz);
		}
		
		for (int i = 0; i < m.nd; i++)
		{
			ArrayList<String> cuv2 = new ArrayList<String>();
			ArrayList<Double> frecv2 = new ArrayList<Double>();
			Set set = m.final_final_sortat.get(i).entrySet();
			Iterator it = set.iterator();
			while (it.hasNext())
			{
				Map.Entry me = (Map.Entry)it.next();
				cuv2.add((String)me.getKey());
				frecv2.add((Double)me.getValue());
			}
			
			while (!adunat.get(i).equals(0))
			{
				cuv2.add(vs.get(i).get(m.n - 1 + adunat.get(i)));
				frecv2.add(vn.get(i).get(m.n - 1+ adunat.get(i)));
				adunat.set(i, adunat.get(i) - 1);
			}
			
			cuv.add(i, cuv2);
			frecv.add(i, frecv2);
		}
		
		/*
		 * verific care documente sunt relevante pentru afisare
		 */
		ArrayList<Integer> doc_ok = new ArrayList<Integer>();
		for (int i = 0; i < m.nd; i++)
			doc_ok.add(1);
		for (int i = 0; i < m.nd; i++)
		{
			for (int j = 0; j < m.nc; j++)
				if (!cuv.get(i).contains(m.v_nc.get(j)))
				{
					doc_ok.set(i, 0);
				}
		}
	
		/*
		 * Le afisez in fisierul dat.
		 */
		FileWriter fstream2 = new FileWriter(args[2]);
		BufferedWriter out = new BufferedWriter(fstream2);
		out.write("Rezultate pentru: (");
		for (int i = 0; i < m.nc - 1; i++)
			out.write(m.v_nc.get(i) + ", ");
		out.write(m.v_nc.get(m.nc - 1) + ")\n");
		out.write("\n");
		
		for (int i = 0; i < m.nd; i++)
		{
			if (doc_ok.get(i).equals(1))
			{
				out.write(m.v_nd.get(i) + " (");
				for (int j = 0; j < m.nc - 1; j++)
				{
					if (cuv.get(i).contains(m.v_nc.get(j)))
						out.write(frecv.get(i).get(cuv.get(i).indexOf(m.v_nc.get(j))) + ", ");
				}
				if (cuv.get(i).contains(m.v_nc.get(m.nc - 1)))
					out.write(frecv.get(i).get(cuv.get(i).indexOf(m.v_nc.get(m.nc - 1))) + ")");
				
				out.write("\n");
			}
		}
		out.close();
		
	}
}

/*
 * Folosesc aceasta clasa pentru a sorta dupa frecventa vectorii
 */
class ValueComparator implements Comparator<String> {

    Map<String, Double> base;
    public ValueComparator(Map<String, Double> base) {
        this.base = base;
    }
  
    public int compare(String a, String b) {
        if (base.get(a) >= base.get(b)) {
            return -1;
        } else {
            return 1;
        } 
    }
}