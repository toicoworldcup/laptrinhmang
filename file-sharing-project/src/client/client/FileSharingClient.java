package client;

import java.io.*;
import java.net.*;

public class FileSharingClient {
    public static void main(String[] args) {
        try {
            // Kết nối đến server
            Socket socket = new Socket("localhost", 12345);
            System.out.println("Đã kết nối đến server.");

            // Tạo BufferedReader và PrintWriter để gửi và nhận dữ liệu
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));

            // Gửi thông điệp "Xin chào từ client!" đến server
            out.println("Xin chào từ client!");

            // Nhận phản hồi từ server
            String serverResponse = in.readLine();
            System.out.println("Server: " + serverResponse); // Nhập tên người dùng

            // Gửi tên người dùng
            System.out.print("Nhập tên người dùng: ");
            String username = userInput.readLine();
            out.println(username);

            // Nhận phản hồi từ server
            serverResponse = in.readLine();
            System.out.println("Server: " + serverResponse); // Nhập mật khẩu

            // Gửi mật khẩu
            System.out.print("Nhập mật khẩu: ");
            String password = userInput.readLine();
            out.println(password);

            // Nhận thông báo đăng nhập thành công từ server
            serverResponse = in.readLine();
            System.out.println("Server: " + serverResponse);

            // Đóng kết nối
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
