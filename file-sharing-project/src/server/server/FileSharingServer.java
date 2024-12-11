package server;

import java.io.*;
import java.net.*;
import java.sql.*;

public class FileSharingServer {
    // Thông tin kết nối đến MySQL
    private static final String DB_URL = "jdbc:mysql://localhost:3306/file_sharing";
    private static final String DB_USER = "root"; // Thay bằng username MySQL của bạn
    private static final String DB_PASSWORD = "1234"; // Thay bằng password MySQL của bạn

    public static void main(String[] args) {
        try {
            // Khởi tạo server socket lắng nghe tại cổng 12345
            ServerSocket serverSocket = new ServerSocket(12345);
            System.out.println("Server đang lắng nghe tại cổng 12345");

            // Chấp nhận kết nối từ client
            Socket clientSocket = serverSocket.accept();
            System.out.println("Kết nối từ " + clientSocket.getInetAddress());

            // Tạo BufferedReader để nhận dữ liệu từ client
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

            // Đọc và xử lý thông điệp đầu tiên từ client
            String clientMessage = in.readLine();
            System.out.println("Nhận từ client: " + clientMessage);

            // Kết nối MySQL
            Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
            System.out.println("Kết nối đến cơ sở dữ liệu thành công!");

            // Kiểm tra nếu thông điệp là "Xin chào từ client!"
            if ("Xin chào từ client!".equals(clientMessage)) {
                // Yêu cầu nhập tên người dùng
                out.println("Nhập tên người dùng:");
                String username = in.readLine();
                System.out.println("Tên người dùng: " + username);

                // Yêu cầu nhập mật khẩu
                out.println("Nhập mật khẩu:");
                String password = in.readLine();
                System.out.println("Mật khẩu: " + password);

                // Lưu thông tin vào cơ sở dữ liệu
                saveUserToDatabase(connection, username, password);

                // Phản hồi thành công
                out.println("Đăng nhập thành công với tên người dùng: " + username);
            }

            // Đóng kết nối
            clientSocket.close();
            serverSocket.close();
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    // Phương thức lưu thông tin tài khoản vào MySQL
    private static void saveUserToDatabase(Connection connection, String username, String password) {
        String query = "INSERT INTO users (username, password) VALUES (?, ?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            preparedStatement.executeUpdate();
            System.out.println("Đã lưu tài khoản vào cơ sở dữ liệu!");
        } catch (SQLException e) {
            System.out.println("Lỗi khi lưu tài khoản: " + e.getMessage());
        }
    }
}
