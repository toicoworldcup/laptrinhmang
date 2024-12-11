package server;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class DatabaseUtils {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/FileSharingDB";
    private static final String DB_USER = "root"; // Thay bằng username MySQL
    private static final String DB_PASSWORD = "1234"; // Thay bằng password MySQL

    public static void saveUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)")) {

            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.executeUpdate();
            System.out.println("Lưu thông tin đăng nhập thành công vào MySQL.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
