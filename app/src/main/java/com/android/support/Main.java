package com.android.support;

import android.app.Activity;
import android.content.Context;
import android.widget.Toast;

public class Main {

    //Load lib
    static {
        // When you change the lib name, change also on Android.mk file
        // Both must have same name
        System.loadLibrary("MixMod");
    }

    private static native void CheckOverlayPermission(Context context);

    public static Menu menu;

    public static void StartWithoutPermission(Context context) {
        CrashHandler.init(context);
        if (context instanceof Activity) {
            //Check if context is an Activity.
            menu = new Menu(context);
            menu.SetWindowManagerActivity();
            menu.ShowMenu();
        } else {
            Toast.makeText(context, "Failed to launch the mod menu\n", Toast.LENGTH_LONG).show();
        }
    }

    public static void ReloadFeatures()
    {
        if (menu != null) {
            menu.ReloadFeatures();
        }
    }

    public static void Start(Context context) {
        CrashHandler.init(context);
        CheckOverlayPermission(context);
    }
}