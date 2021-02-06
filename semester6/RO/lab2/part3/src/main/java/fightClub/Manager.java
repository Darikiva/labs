package fightClub;

import java.util.ArrayList;
import java.util.Random;

public class Manager {
    static ArrayList<Fighter> fighters = new ArrayList<>();

    Manager(int amount) {
        fighters.clear();
        for (int i = 0; i < amount; ++i) {
            Random rand = new Random();
            int power = rand.nextInt() % 100;
            fighters.add(new Fighter(power, true));
            System.out.print(power + " ");
        }
        System.out.print(fighters.size());

    }

    public int work() {
        Battle battle = new Battle(0, fighters.size());
        return battle.compute();
    }

}
