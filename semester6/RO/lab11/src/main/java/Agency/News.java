package Agency;

public class News {
	private Long id;
	private Long category_id;
	private String name;
	private Long words;

	public Long getId() {
		return id;
	}
	public Long getWords() {
		return words;
	}
	public void setWords(Long population) {
		this.words = population;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public Long getCategoryId() {
		return category_id;
	}
	public void setCategoryId(Long countryId) {
		this.category_id = countryId;
	}
	public void setId(Long id) {
		this.id = id;
	}
}
