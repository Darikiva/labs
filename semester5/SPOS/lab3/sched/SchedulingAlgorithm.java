// Run() is called from Scheduling.main() and is where
// the scheduling algorithm written by the user resides.
// User modification should occur within the Run() function.

import java.util.Vector;
import java.io.*;

public class SchedulingAlgorithm {

    public static Results Run(int runtime, Vector processVector, Results result, int wat) {
        int i = 0;
        int comptime = 0;
        int currentProcess = 0;
        int previousProcess = 0;
        int size = processVector.size();
        int completed = 0;
        String resultsFile = "Summary-Processes";
        int[] times = new int[size];

        result.schedulingType = "Batch (Nonpreemptive)";
        result.schedulingName = "First-Come First-Served";
        try {
            //BufferedWriter out = new BufferedWriter(new FileWriter(resultsFile));
            //OutputStream out = new FileOutputStream(resultsFile);
            PrintStream out = new PrintStream(new FileOutputStream(resultsFile));
            sProcess process = (sProcess) processVector.elementAt(currentProcess);
            out.println("Process: " + currentProcess + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
            while (comptime < runtime) {
                int min = 0, max = 0;
                for (i = 0; i < size; ++i) {
                    if (times[i] != -1) {
                        sProcess pr = (sProcess) processVector.elementAt(i);
                        if (pr.cpudone == pr.cputime) {
                            times[i] = -1;
                        }
                        if (times[i] < min) {
                            min = times[i];
                        } else if (times[i] > max) {
                            times[i] = max;
                        }
                    }
                }
                if (process.cpudone == process.cputime) {
                    completed++;
                    out.println("Process: " + currentProcess + " completed... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                    if (completed == size) {
                        result.compuTime = comptime;
                        out.close();
                        return result;
                    }
                    double min_coef = Double.MAX_VALUE;
                    for (i = size - 1; i >= 0; i--) {
                        process = (sProcess) processVector.elementAt(i);
                        if (process.cpudone < process.cputime) {
                            double new_coef = (float) process.cpudone / process.lifetime;
                            if (new_coef < min_coef) {
                                currentProcess = i;
                                min_coef = process.cpudone;
                            }
                        }
                    }
                    process = (sProcess) processVector.elementAt(currentProcess);
                    out.println("Process: " + currentProcess + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                } else if (max - min >= wat) {
                    double min_coef = Double.MAX_VALUE;
                    for (i = size - 1; i >= 0; i--) {
                        process = (sProcess) processVector.elementAt(i);
                        if (process.cpudone < process.cputime) {
                            double new_coef = (float) process.cpudone / (process.lifetime * process.weight * (size - completed));
                            if (new_coef < min_coef) {
                                currentProcess = i;
                                min_coef = new_coef;
                            }
                        }
                    }
                    process = (sProcess) processVector.elementAt(currentProcess);
                    process.phasetime = 0;
                    out.println("Process: " + currentProcess + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                }
                if (process.ioblocking == process.ionext) {
                    out.println("Process: " + currentProcess + " I/O blocked... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                    process.numblocked++;
                    process.ionext = 0;
                    previousProcess = currentProcess;
                    double min_coef = Double.MAX_VALUE;
                    for (i = size - 1; i >= 0; i--) {
                        process = (sProcess) processVector.elementAt(i);
                        if (process.cpudone < process.cputime && previousProcess != i) {
                            double new_coef = (float) process.cpudone / (process.lifetime * process.weight * (size - completed));
                            if (new_coef < min_coef) {
                                currentProcess = i;
                                min_coef = new_coef;
                            }
                        }
                    }
                    process = (sProcess) processVector.elementAt(currentProcess);
                    process.phasetime = 0;
                    out.println("Process: " + currentProcess + " registered... (" + process.cputime + " " + process.ioblocking + " " + process.cpudone + " " + process.cpudone + ")");
                }
                process.cpudone++;
                for (int j = 0; j < size; ++j) {
                    process = (sProcess) processVector.elementAt(j);
                    ++process.lifetime;
                }
                process = (sProcess) processVector.elementAt(currentProcess);
                times[currentProcess]++;
                if (process.ioblocking > 0) {
                    process.ionext++;
                }
                comptime++;
            }
            out.close();
        } catch (IOException e) { /* Handle exceptions */ }
        result.compuTime = comptime;
        return result;
    }
}
