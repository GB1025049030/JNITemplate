package ohos.bundlemgr;

import com.pandon.javaapi.annotation.JNIClass;
import com.pandon.javaapi.annotation.JNIField;

@JNIClass
public class PackageInstalledStatus {
    @JNIField(sign = "Ljava/lang/String;")
    private String shellInstalledDir;
    @JNIField(sign = "I")
    private int status = 1;
    @JNIField(sign = "Ljava/lang/String;")
    private String statusMessage;

    public int getStatus() {
        return this.status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public String getStatusMessage() {
        return this.statusMessage;
    }

    public void setStatusMessage(String statusMessage) {
        this.statusMessage = statusMessage;
    }

    public String getShellInstalledDir() {
        return this.shellInstalledDir;
    }

    public void setShellInstalledDir(String shellInstalledDir) {
        this.shellInstalledDir = shellInstalledDir;
    }
}
