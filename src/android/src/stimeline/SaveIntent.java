package stimeline;

import android.net.Uri;
import java.io.File;
import android.util.Log;
import android.content.Intent;
import org.qtproject.qt5.android.bindings.QtActivity;
//import android.support.v4.content.FileProvider;
import android.support.v4.content.ContextCompat;
import android.content.pm.PackageManager;
import android.Manifest;

public class SaveIntent extends QtActivity
{
    public void save(String fileUri) {
        Log.i("BOoom", fileUri);
        final File file = new File(fileUri);
        Log.i("Boom2", Uri.fromFile(file).toString());
        // Modified from https://developer.android.com/training/sharing/send.html
        Intent shareIntent = new Intent();
        shareIntent.setAction(Intent.ACTION_SEND);
        shareIntent.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(file));
        shareIntent.setType("application/zip");
        startActivity(Intent.createChooser(shareIntent, "Send file to"));
    }

    public boolean isWritableStorage() {
        // https://developer.android.com/training/permissions/requesting.html
        int permissionCheck = ContextCompat.checkSelfPermission(thisActivity,
            Manifest.permission.WRITE_EXTERNAL_STORAGE);

        if (permissionCheck ==  PackageManager.PERMISSION_GRANTED)
            return true;

        return false;
    }

    public boolean requestWritableStorage() {
        // https://developer.android.com/training/permissions/requesting.html
        // Here, thisActivity is the current activity
        if (ContextCompat.checkSelfPermission(thisActivity,
            Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(thisActivity,
                new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE},
                1);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           String permissions[],
                                           int[] grantResults) {
        switch (requestCode) {
            case 1: {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0
                    && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    // TODO: callback Qt code?
                } else {
                    // Permission not granted
                }
                return;
            }
        }
    }
}
