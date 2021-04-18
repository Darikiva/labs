package Agency;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class Agency {
    private ArrayList<Category> categories;
    private ArrayList<News> news_list;
    private int id_generator_category;
    private int id_generator_news;

    public Agency() {
        categories = new ArrayList<>();
        news_list = new ArrayList<>();
        id_generator_category = 0;
        id_generator_news = 0;
    }

    public Category getCategoryById(int id) {
        for (Category category : categories) {
            if (category.getId() == id) {
                return category;
            }
        }
        return null;
    }

    public void addCategory(int id, String name) {
        if (getCategoryById(id) == null) {
            categories.add(new Category(id, name));
        }
    }

    public void addCategory(Category category) {
        if (getCategoryById(category.getId()) == null) {
            categories.add(category);
        }
    }

    public Category getCategoryByIndex(int index) {
        return categories.get(index);
    }

    public Category getCategoryByName(String name) {
        for (Category category : categories) {
            if (category.getName().equals(name)) {
                return category;
            }
        }
        return null;
    }

    public ArrayList<Category> getCategories() {
        return categories;
    }

    public News getNewsByName(String name) {
        for (News news : news_list) {
            if (news.getName().equals(name)) {
                return news;
            }
        }
        return null;
    }

    public void addNews(int id, String name, int category_id) {
        Category category = getCategoryById(category_id);
        if (category != null) {
            for (News news : news_list) {
                if (news.getId() == id) {
                    return;
                }
            }
            news_list.add(new News(id, name, category));
        }
    }

    public void addNews(News news) {
        Category category = getCategoryById(news.getCategory().getId());
        if (category != null) {
            if (getNewsById(news.getId()) == null)
                news_list.add(news);
        }
    }

    public News getNewsById(int id) {
        for (News news : news_list) {
            if (news.getId() == id) {
                return news;
            }
        }
        return null;
    }

    public News getNewsByIndex(int index) {
        return news_list.get(index);
    }

    public void loadFromFile(String filename) {
        SchemaFactory sf = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
        Schema s = null;
        try {
            s = sf.newSchema(new File("saving.xsd"));
        } catch (SAXException e1) {
            e1.printStackTrace();
        }
        DocumentBuilderFactory dbf = null;
        DocumentBuilder db = null;
        try {
            dbf = DocumentBuilderFactory.newInstance();
            dbf.setValidating(false);
            dbf.setSchema(s);
            db = dbf.newDocumentBuilder();
            db.setErrorHandler(new MyErrorHandler());
        } catch (ParserConfigurationException e) {
            System.out.println(e.getStackTrace());
        }
        Document doc = null;
        try {
            doc = db.parse(new File(filename));
        } catch (SAXException ex) {
        } catch (IOException ex) {
        }
        Element root = doc.getDocumentElement();
        if (root.getTagName().equals("agency")) {
            NodeList listCountries = root.getElementsByTagName("category");
            for (int i = 0; i < listCountries.getLength(); i++) {
                Element category = (Element) listCountries.item(i);
                String category_id = category.getAttribute("id");
                if (Integer.parseInt(category_id) >= id_generator_category) {
                    id_generator_category = Integer.parseInt(category_id) + 1;
                }
                String category_name = category.getAttribute("name");
                addCategory(Integer.parseInt(category_id), category_name);
                NodeList list_news = category.getElementsByTagName("news");
                for (int j = 0; j < list_news.getLength(); j++) {
                    Element news = (Element) list_news.item(j);
                    String news_name = news.getAttribute("name");
                    String news_id = news.getAttribute("id");
                    if (Integer.parseInt(news_id) >= id_generator_news) {
                        id_generator_news = Integer.parseInt(news_id) + 1;
                    }
                    addNews(Integer.parseInt(news_id), news_name, Integer.parseInt(category_id));
                }
            }
        }
    }

    public void saveToFile(String filename) {
        DocumentBuilderFactory dbf = null;
        DocumentBuilder db = null;
        Document doc = null;
        dbf = DocumentBuilderFactory.newInstance();
        try {
            db = dbf.newDocumentBuilder();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        }
        doc = db.newDocument();
        Element root = doc.createElement("agency");
        doc.appendChild(root);
        for (Category category : categories) {
            Element categElement = doc.createElement("category");
            categElement.setAttribute("id", String.valueOf(category.getId()));
            categElement.setAttribute("name", category.getName());
            for (News news : category.getNews()) {
                Element newsElement = doc.createElement("news");
                newsElement.setAttribute("id", String.valueOf(news.getId()));
                newsElement.setAttribute("name", String.valueOf(news.getName()));
                categElement.appendChild(newsElement);
            }
            root.appendChild(categElement);
        }

        Source domSource = new DOMSource(doc);
        Result fileResult = new StreamResult(new File(filename));
        TransformerFactory factory = TransformerFactory.newInstance();
        Transformer transformer;
        try {
            transformer = factory.newTransformer();
            transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
            transformer.transform(domSource, fileResult);
        } catch (TransformerConfigurationException e) {
            e.printStackTrace();
        } catch (TransformerException e) {
            e.printStackTrace();
        }
    }

    int generateIdCategory() {
        int answer = id_generator_category;
        ++id_generator_category;
        return answer;
    }

    int generateIdNews() {
        int answer = id_generator_news;
        ++id_generator_news;
        return answer;
    }

    void deleteCategory(int id) {
        Category category = getCategoryById(id);
        if (category != null) {
            categories.remove(category);
        }
    }

    void deleteNews(int id) {
        News news = getNewsById(id);
        if (news != null) {
            news_list.remove(news);
        }
    }
}
