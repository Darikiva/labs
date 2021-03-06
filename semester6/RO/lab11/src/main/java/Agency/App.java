package Agency;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.List;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

public class App extends JFrame {
	private static Category stat_category = null;
	private static News stat_news = null;

	private static boolean editMode = false;
	private static boolean categoryMode = true;

	private static JButton btnAddCategory = new JButton("Add category");
	private static JButton btnAddNews = new JButton("Add news");
	private static JButton btnEdit = new JButton("Edit Data");
	private static JButton btnCancel = new JButton("Cancel");
	private static JButton btnSave = new JButton("Save");
	private static JButton btnDelete = new JButton("Delete");

	private static Box menuPanel = Box.createVerticalBox();
	private static Box actionPanel = Box.createVerticalBox();
	private static Box comboPanel = Box.createVerticalBox();
	private static Box newsPanel = Box.createVerticalBox();
	private static Box categoryPanel = Box.createVerticalBox();

	private static JComboBox comboCategory = new JComboBox();
	private static JComboBox comboNews = new JComboBox();

	private static JTextField tfCategoryName = new JTextField(30);
	private static JTextField tfNewsName = new JTextField(30);
	private static JTextField tfNewsCategoryName = new JTextField(30);

	private static JFrame frame;

	App() {
		super("News agency");
		frame = this;
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		this.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent event) {
				frame.dispose();
				System.exit(0);
			}
		});
		Box box = Box.createVerticalBox();

		// Menu
		menuPanel.add(btnAddCategory);
		menuPanel.add(btnAddNews);
		menuPanel.add(btnEdit);

		btnAddCategory.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent event) {
				editMode = false;
				categoryMode = true;
				menuPanel.setVisible(false);
				comboPanel.setVisible(false);
				newsPanel.setVisible(false);

				categoryPanel.setVisible(true);
				actionPanel.setVisible(true);
				// setContentPane(box);
				pack();
			}
		});
		btnAddNews.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent event) {
				editMode = false;
				categoryMode = false;
				menuPanel.setVisible(false);
				comboPanel.setVisible(false);
				categoryPanel.setVisible(false);

				newsPanel.setVisible(true);
				actionPanel.setVisible(true);
				// setContentPane(box);
				pack();
			}
		});
		btnEdit.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent event) {
				menuPanel.setVisible(false);
				categoryPanel.setVisible(false);
				newsPanel.setVisible(false);

				editMode = true;
				comboPanel.setVisible(true);
				actionPanel.setVisible(true);
				// setContentPane(box);
				pack();
			}
		});

		// ComboBoxes
		comboPanel.add(new JLabel("Category:"));
		comboPanel.add(comboCategory);
		comboPanel.add(new JLabel("News:"));
		comboPanel.add(comboNews);

		comboCategory.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String name = (String) comboCategory.getSelectedItem();
				stat_category = CategoryDAO.findByName(name);
				categoryMode = true;
				categoryPanel.setVisible(true);
				newsPanel.setVisible(false);
				fillCategoryFields();
				// setContentPane(box);
				pack();
			}
		});
		comboNews.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String name = (String) comboNews.getSelectedItem();
				stat_news = NewsDAO.findByName(name);
				categoryMode = false;
				categoryPanel.setVisible(false);
				newsPanel.setVisible(true);
				fillNewsFields();
				// setContentPane(box);
				pack();
			}
		});
		fillComboBoxes();

		// City Fields
		newsPanel.add(new JLabel("Name:"));
		newsPanel.add(tfNewsName);
		newsPanel.add(new JLabel("Category Name:"));
		newsPanel.add(tfNewsCategoryName);

		// Country Fields
		categoryPanel.add(new JLabel("Name:"));
		categoryPanel.add(tfCategoryName);

		// Action Bar
		actionPanel.add(btnSave);
		actionPanel.add(btnDelete);
		actionPanel.add(btnCancel);
		btnSave.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent event) {
				save();
			}
		});
		btnDelete.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent event) {
				delete();
			}
		});
		btnCancel.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent event) {
				clearFields();
				menuPanel.setVisible(true);
				comboPanel.setVisible(false);
				categoryPanel.setVisible(false);
				newsPanel.setVisible(false);
				actionPanel.setVisible(false);
				// setContentPane(box);
				pack();
			}
		});

		menuPanel.setVisible(true);
		actionPanel.setVisible(false);
		comboPanel.setVisible(false);
		newsPanel.setVisible(false);
		categoryPanel.setVisible(false);

		clearFields();
		box.add(menuPanel);
		box.add(comboPanel);
		box.add(categoryPanel);
		box.add(newsPanel);
		box.add(actionPanel);
		setContentPane(box);
		pack();
	}

	private static void save() {
		if (editMode) {
			if (categoryMode) {
				String oldname = stat_category.getName();
				String newname = tfCategoryName.getText();
				Category category = CategoryDAO.findByName(oldname);
				if (category != null) {
					if (CategoryDAO.findByName(newname) != null) {
						JOptionPane.showMessageDialog(null, "Error: category with this name already exists!");
					} else {
						category.setName(newname);
						comboCategory.removeItem(oldname);
						comboCategory.addItem(newname);
						comboCategory.setSelectedIndex(comboCategory.getItemCount() - 1);
					}
				}
			} else {
				String oldname = stat_news.getName();
				String newname = tfNewsCategoryName.getText();
				News news = NewsDAO.findByName(oldname);
				if (news != null) {
					if (NewsDAO.findByName(newname) != null) {
						JOptionPane.showMessageDialog(null, "Error: news with this name already exists!");
					} else {
						news.setName(newname);
						comboNews.removeItem(oldname);
						comboNews.addItem(newname);
						comboNews.setSelectedIndex(comboNews.getItemCount() - 1);
					}
				}
			}
		} else {
			if (categoryMode) {
				String name = tfCategoryName.getText();
				if (CategoryDAO.findByName(name) == null) {
					Category category = new Category();
					category.setName(name);
					CategoryDAO.insert(category);
					comboCategory.addItem(category.getName());
				} else {
					JOptionPane.showMessageDialog(null, "Error: category with this name already exists!");
				}
			} else {
				String name = tfNewsName.getText();
				if (NewsDAO.findByName(name) == null) {
					String cat_name = tfNewsCategoryName.getText();
					Category category = CategoryDAO.findByName(cat_name);
					if (category == null) {
						JOptionPane.showMessageDialog(null, "Error: no category with this name!");
					} else {
						News new_news = new News();
						new_news.setName(name);
						new_news.setCategoryId(category.getId());
						NewsDAO.insert(new_news);
						comboNews.addItem(name);
					}
				} else {
					JOptionPane.showMessageDialog(null, "Error: news with this name already exists!");
				}
			}
		}
		editMode = false;
		menuPanel.setVisible(true);
		comboPanel.setVisible(false);
		categoryPanel.setVisible(false);
		newsPanel.setVisible(false);
		actionPanel.setVisible(false);
	}

	private static void delete() {
		if (editMode) {
			if (categoryMode) {
				CategoryDAO.delete(stat_category);
				for (News c : NewsDAO.findAll()) {
					if (c.equals(stat_news)) {
						stat_news = null;
					}
					if (c.getCategoryId().equals(stat_category.getId())) {
						comboNews.removeItem(c.getName());
						NewsDAO.delete(c);
					}
				}
				comboCategory.removeItem(stat_category.getName());
				stat_category = null;
			} else {
				NewsDAO.delete(stat_news);
				comboNews.removeItem(stat_news.getName());
				stat_news = null;
			}
		}
	}

	private void fillComboBoxes() {
		comboCategory.removeAllItems();
		comboNews.removeAllItems();
		List<Category> categories = CategoryDAO.findAll();
		for (Category category : categories) {
			comboCategory.addItem(category.getName());
		}
		for (News news : NewsDAO.findAll()) {
			comboNews.addItem(news.getName());
		}
	}

	private static void clearFields() {
		tfCategoryName.setText("");
		tfNewsName.setText("");
		tfNewsCategoryName.setText("");
		stat_category = null;
		stat_news = null;
	}

	private static void fillCategoryFields() {
		if (stat_category == null)
			return;
		tfCategoryName.setText(stat_category.getName());
	}

	private static void fillNewsFields() {
		if (stat_news == null)
			return;
		tfNewsName.setText(stat_news.getName());
		tfNewsCategoryName.setText(CategoryDAO.findById(stat_news.getCategoryId()).getName());
	}

	public static void main(String[] args) {
		JFrame myWindow = new App();
		myWindow.setVisible(true);
	}
}
