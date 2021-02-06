package vinnie;

public class Main {

    public static void main(String[] args) {
        Manager manager = new Manager();
        manager.work();
        System.out.println(Manager.row + " " + Manager.column);
    }
}
