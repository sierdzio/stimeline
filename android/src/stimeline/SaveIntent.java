package stimeline;

import android.app.Activity;
import android.app.NativeActivity;
import android.content.Context;
import android.content.Intent;

class SaveIntent extends org.qtproject.qt5.android.bindings.QtActivity
{
    void save() {
        Intent sendIntent = new Intent();
        sendIntent.setAction(Intent.ACTION_SEND);
        sendIntent.putExtra(Intent.EXTRA_TEXT, "This is my text to send. Hello from Qt");
        sendIntent.setType("text/plain");
        startActivity(sendIntent);
    }
}
