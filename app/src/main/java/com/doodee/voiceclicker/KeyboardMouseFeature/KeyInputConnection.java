package com.doodee.voiceclicker.KeyboardMouseFeature;

import android.view.inputmethod.BaseInputConnection;

public class KeyInputConnection extends BaseInputConnection {

    CustomKeyboardCaptureView view;

    public KeyInputConnection(CustomKeyboardCaptureView targetView, boolean fullEditor) {
        super(targetView, fullEditor);
        view = targetView;
    }

    @Override
    public boolean commitText(CharSequence text, int newCursorPosition) {
        view.sendChars(text);
        return true;
    }


}
