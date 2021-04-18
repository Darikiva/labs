package Agency;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class NewsDAO {
	public static News findById(long id) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"SELECT * "
					+ "FROM news "
					+ "WHERE id = ?";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setLong(1, id);
			ResultSet rs = st.executeQuery();	
			News news = null;
			if(rs.next()) {	
				news = new News();
				news.setId(rs.getLong(1));
				news.setName(rs.getString(2));
				news.setCategoryId(rs.getLong(3));
				// news.setWords(rs.getLong(4));
			}
			st.close();
			return news;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return null;
	}
	
	public static News findByName(String name) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"SELECT * "
					+ "FROM news "
					+ "WHERE name = ?";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setString(1, name);
			ResultSet rs = st.executeQuery();	
			News news = null;
			if(rs.next()) {	
				news = new News();
				news.setId(rs.getLong(1));
				news.setName(rs.getString(2));
				news.setCategoryId(rs.getLong(3));
				// news.setWords(rs.getLong(4));
			}
			st.close();
			return news;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return null;
	}
	
	public static boolean update(News news) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"UPDATE news "
					+ "SET name = ?, category_id = ?"
					+ "WHERE id = ?";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setString(1, news.getName());
			st.setLong(2, news.getCategoryId());
			// st.setLong(3, news.getWords());
			st.setLong(4, news.getId());
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
	
	public static boolean insert(News news) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"INSERT INTO news (name,category_id) "
					+ "VALUES (?,?) "
					+ "RETURNING id";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setString(1, news.getName());
			st.setLong(2, news.getCategoryId());
			// st.setLong(3, news.getWords());
			ResultSet rs = st.executeQuery();	
			if(rs.next()) {
				news.setId(rs.getLong(1));
			} else
				return false;
			st.close();
			return true;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return false;
	}
	
	public static boolean delete(News news) {
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"DELETE FROM news "
					+ "WHERE id = ?";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setLong(1, news.getId());
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
	
	public static List<News> findAll(){
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"SELECT * "
					+ "FROM news";		
			PreparedStatement st = connection.prepareStatement(sql);
			ResultSet rs = st.executeQuery();			
			List<News> list = new ArrayList<>();
			while(rs.next()) {
				News news = new News();
				news.setId(rs.getLong(1));
				news.setName(rs.getString(2));
				news.setCategoryId(rs.getLong(3));
				// news.setWords(rs.getLong(4));
				list.add(news);
			}
			st.close();
			return list;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return null;
	}
	
	public static List<News> findByCategoryId(Long id){
		try(Connection connection = DBConnection.getConnection();) {
			String sql = 
					"SELECT * "
					+ "FROM news "
					+ "WHERE category_id = ?";		
			PreparedStatement st = connection.prepareStatement(sql);
			st.setLong(1, id);
			ResultSet rs = st.executeQuery();
			List<News> list = new ArrayList<>();
			while(rs.next()) {
				News news = new News();
				news.setId(rs.getLong(1));
				news.setName(rs.getString(2));
				news.setCategoryId(rs.getLong(3));
				// news.setWords(rs.getLong(4));
				list.add(news);
			}
			st.close();
			return list;
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
		return null;
	}
}
