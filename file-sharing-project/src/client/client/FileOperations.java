package client;

import java.io.*;
import java.net.*;

public class FileOperations {
    private Socket socket;

    public FileOperations(Socket socket) {
        this.socket = socket;
    }

    public void uploadFile(File file) {
        try (BufferedInputStream fileIn = new BufferedInputStream(new FileInputStream(file));
             OutputStream out = socket.getOutputStream()) {

            byte[] buffer = new byte[4096];
            int bytesRead;

            while ((bytesRead = fileIn.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }

            System.out.println("Upload file thành công!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void downloadFile(String fileName) {
        try (BufferedOutputStream fileOut = new BufferedOutputStream(new FileOutputStream("downloaded_" + fileName));
             InputStream in = socket.getInputStream()) {

            byte[] buffer = new byte[4096];
            int bytesRead;

            while ((bytesRead = in.read(buffer)) != -1) {
                fileOut.write(buffer, 0, bytesRead);
            }

            System.out.println("Download file thành công!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
