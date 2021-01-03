public class sProcess {
  public int cputime;
  public int ioblocking;
  public int cpudone;
  public int ionext;
  public int numblocked;
  public int lifetime;
  public int phasetime;
  public int weight;

  public sProcess (int cputime, int ioblocking, int cpudone, int ionext, int numblocked, int lifetime, int weight) {
    this.cputime = cputime;
    this.ioblocking = ioblocking;
    this.cpudone = cpudone;
    this.ionext = ionext;
    this.numblocked = numblocked;
    this.lifetime = lifetime;
    this.weight = weight;
    this.phasetime = 0;
  } 	
}
