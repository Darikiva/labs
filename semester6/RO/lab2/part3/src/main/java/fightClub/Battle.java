package fightClub;

import java.util.concurrent.RecursiveTask;

public class Battle extends RecursiveTask<Integer> {

    int m_left, m_right;

    public Battle(int left, int right) {
        this.m_left = left;
        this.m_right = right;
    }

    @Override
    protected Integer compute() {
        if (m_right - m_left < 3) {
            return fight(m_left, m_left + 1);
        } else {
            int middle = (m_left + m_right) / 2;
            Battle battle_left = new Battle(m_left, middle);
            Battle battle_right = new Battle(middle, m_right);
            battle_left.fork();
            battle_right.fork();
            int lhs = battle_left.join();
            int rhs = battle_right.join();
            return fight(lhs, rhs);
        }
    }

    int fight(int lhs, int rhs) {
        Fighter left = Manager.fighters.get(lhs);
        Fighter right = Manager.fighters.get(rhs);
        int winner;
        if (left.getPower() < right.getPower()) {
            left.defeat();
            winner = rhs;
        } else {
            right.defeat();
            winner = lhs;
        }
        return winner;
    }
}
