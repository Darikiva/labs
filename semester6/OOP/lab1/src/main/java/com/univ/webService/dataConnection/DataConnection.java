package com.univ.webService.dataConnection;

import org.apache.commons.dbcp2.BasicDataSource;

import javax.sql.DataSource;
import java.sql.*;
import java.util.Properties;


public class DataConnection {

    private static final DataSource datasource = createDataSource();

    public static Connection getDBConnection() throws SQLException {
        return datasource.getConnection();
    }

    private static DataSource createDataSource() {
        Properties env = loadJdbcPropertiesFromClassPath();
        BasicDataSource datasource = new BasicDataSource();
        datasource.setDriverClassName(env.getProperty("jdbc.driverClassName"));
        datasource.setUrl(env.getProperty("jdbc.url"));
        datasource.setUsername(env.getProperty("jdbc.username"));
        datasource.setPassword(env.getProperty("jdbc.password"));
        return datasource;
    }

    private static Properties loadJdbcPropertiesFromClassPath() {
        Properties properties = new Properties();
        properties.setProperty("jdbc.driverClassName", "org.postgresql.Driver");
        properties.setProperty("jdbc.url", "jdbc:postgresql://localhost:5432/library");
        properties.setProperty("jdbc.username", "postgres");
        properties.setProperty("jdbc.password", "user");
        return properties;
    }


    public static void updateDB(String sqlQuery) throws SQLException {
        Connection connection = DataConnection.getDBConnection();
        PreparedStatement pstmt = connection.prepareStatement(sqlQuery);
        pstmt.executeUpdate(sqlQuery);
        connection.close();

    }
}
