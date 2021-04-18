package Agency;

public class News {
    private int id;
    private String name;
    private Category category;

    public Category getCategory() {
        return category;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setCategory(Category category) {
        this.category = category;
    }

    public News(int id, String name, Category category) {
        this.id = id;
        this.name = name;
        this.category = category;
        category.addNews(this);
    }

    public News(){}
}
