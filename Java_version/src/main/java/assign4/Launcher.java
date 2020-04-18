package assign4;

import java.util.Random;

public class Launcher {
	public static void main(String[] args) {
		if(args.length != 1){
			System.out.println("USAGE: java Launcher <integer>");
			System.exit(1);
		}
		
		int arraySize = Integer.parseInt(args[0]);
		
		double unsortedM[] = new double[arraySize];
		Runnable r = new MyClass(arraySize, 0, arraySize, unsortedM, false, "1");
		new Thread(r).start(); // Runs the single thread
		
		Runnable r2 = new MyClass(arraySize, 0, arraySize, unsortedM, true, "2");
		new Thread(r2).start(); // Runs the multi-thread
	}
}

class MyClass implements Runnable {
	int arraySize, start, end, mid;
	boolean bMulti; 
	double unsortedM[];
	long execStart, execEnd;
	String threadName;
	
	public MyClass(int arraySize, int start, int end, double[] unsortedM, boolean bMulti, String threadName){
		this.arraySize = arraySize;
		this.start = start;
		this.end = end;
		this.unsortedM = unsortedM;
		this.bMulti = bMulti;
		this.threadName = threadName;
	}
	
	public void run() {
		if(this.bMulti){ // Run 2 threads
			this.mid = this.arraySize / 2;
			this.execStart = System.currentTimeMillis();
			this.setRandom(); // Randomize entire Array
			this.sort(0,  this.mid); // SortJoins on first halve
			// calls second thread to sortJoin on second halve
			Runnable r = new MyClass(this.mid, this.mid, arraySize, unsortedM, false, "2");
			new Thread(r).start(); // Runs the single thread
			this.execEnd = System.currentTimeMillis();
			System.out.println("Sorting is done in " + (execEnd - execStart) + "ms " + "when " 
					+ this.threadName + " thread(s) used.");
		}
		else{
			this.execStart = System.currentTimeMillis();
			if(! this.threadName.equals("2"))
				this.setRandom();
			this.sort(this.start, this.end);
			this.execEnd = System.currentTimeMillis();
			System.out.println("Sorting is done in " + (execEnd - execStart) + "ms " + "when " 
			+ this.threadName + " thread(s) used.");
		}
	}
	
	public void sort(int iStart, int iEnd){
		int i, j, iMinIndex;
		double dTemp;
		
		for(i = iStart; i < iEnd; i++){
			iMinIndex = i;
			for(j = i + 1; j < iEnd; j++){
				if(this.unsortedM[j] < this.unsortedM[iMinIndex]){
					iMinIndex = j;
				}
			}
			// insert values into the array
			dTemp = this.unsortedM[iMinIndex];
			this.unsortedM[iMinIndex] = this.unsortedM[i];
			this.unsortedM[i] = dTemp;
		}
	}
	
	public void setRandom(){
		Random rand = new Random();
		
		for(int i = this.start; i < this.end; i++){
			this.unsortedM[i] = rand.nextInt(1000) * 1.0;
		}
	}
}
