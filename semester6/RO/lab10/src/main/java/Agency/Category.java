package Agency;

import java.util.ArrayList;

public class Category {
    private int id;
    private String name;
    private ArrayList<News> news_list = new ArrayList<>();

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Category(int id, String name) {
        this.id = id;
        this.name = name;
        news_list = new ArrayList<>();
    }

    public void addNews(News news) {
        news_list.add(news);
    }

    public ArrayList<News> getNews() {
        return news_list;
    }

    public Category(){
    }
}
