package fightClub;

public class Fighter {
    int m_power;
    boolean m_is_alive;

    public Fighter(int m_power, boolean m_is_alive) {
        this.m_power = m_power;
        this.m_is_alive = m_is_alive;
    }

    public int getPower() {
        return m_power;
    }

    public void setPower(int m_power) {
        this.m_power = m_power;
    }

    public boolean isAlive() {
        return m_is_alive;
    }

    public void defeat() {
        this.m_is_alive = false;
    }

    
    
}
