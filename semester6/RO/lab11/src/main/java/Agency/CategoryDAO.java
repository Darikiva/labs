package Agency;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class CategoryDAO {
	public static Category findById(long id) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"SELECT * "
					+ "FROM category "
					+ "WHERE id = ?";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setLong(1, id);
			ResultSet rs = st.executeQuery();	
			Category category = null;
			if(rs.next()) {	
				category = new Category();
				category.setId(rs.getLong(1));
				category.setName(rs.getString(2));
			}
			st.close();
			return category;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return null;
	}
	
	public static Category findByName(String name) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"SELECT * "
					+ "FROM category "
					+ "WHERE name = ?";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setString(1, name);
			ResultSet rs = st.executeQuery();	
			Category category = null;
			if(rs.next()) {	
				category = new Category();
				category.setId(rs.getLong(1));
				category.setName(rs.getString(2));
			}
			st.close();
			return category;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return null;
	}
	
	public static boolean update(Category category) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"UPDATE category "
					+ "SET name = ? "
					+ "WHERE id = ?";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setString(1, category.getName());
			st.setLong(4, category.getId());
			int result = st.executeUpdate();
			st.close();
			if(result>0)
				return true;
			else
				return false;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return false;
	}
	
	public static boolean insert(Category category) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"INSERT INTO category (name) "
					+ "VALUES (?) "
					+ "RETURNING id";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setString(1, category.getName());
			ResultSet rs = st.executeQuery();
			if(rs.next()) {
				category.setId(rs.getLong(1));
			} else
				return false;
			st.close();	
			return true;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return false;
	}
	
	public static boolean delete(Category category) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"DELETE FROM category "
					+ "WHERE id = ?";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setLong(1, category.getId());
			int result = st.executeUpdate();
			st.close();
			if(result>0)
				return true;
			else
				return false;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return false;
	}
	
	public static List<Category> findAll(){
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"SELECT * "
					+ "FROM category";		
			PreparedStatement st = connection.prepareStatement(sql);
			ResultSet rs = st.executeQuery();			
			List<Category> list = new ArrayList<>();
			while(rs.next()) {
				Category category = new Category();
				category.setId(rs.getLong(1));
				category.setName(rs.getString(2));
				list.add(category);
			}
			st.close();
			return list;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return null;
	}
}
