import java.util.Random; 

public class Launcher {
    int iArraySize;
    double[] iUnsortedM;

    public static void main(String[] args){
        if(args.length != 1){
            System.out.println("USAGE: java Launcher <integer>");
            System.exit(0);
        }
        
        iArraySize = Integer.parseInt(args[0]);
        iUnsortedM = new double[iArraySize];

    }

    public void generateRandom(){
        Random rand = new Random();

        for(int i = 0; i < this.iArraySize; i++){
            this.iUnsortedM[i] = rand.nextDouble(1000);
        }
    }
}
