package com.pandon.javaapi.processor;

import com.pandon.javaapi.processor.Constants.MethodFlag;

public class ArgumentBase {
    public String clsName;
    public String sign;
    public int flag;
    public int arrayDimension;

    public ArgumentBase(String sign) {
        this.sign = sign;
    }

    public ArgumentBase(String clsName, String sign, int flag, int arrayDimension) {
        this.clsName = clsName;
        this.sign = sign;
        this.flag = flag;
        this.arrayDimension = arrayDimension;
    }

    public void parseFieldSign() {
        parseFieldSign(0);
    }

    public void parseFieldSign(int flagBase) {
        int _arrayDimension = 0;
        if (sign.startsWith(Constants.SYMBOL_SQUARE_BRACKETS_LEFT)) {
            int _index = sign.lastIndexOf(Constants.SYMBOL_SQUARE_BRACKETS_LEFT);
            if (_index != -1) {
                _arrayDimension = _index + 1;
            }
        }
        char symbol = sign.charAt(sign.length() - 1);
        int _flag = flagBase | parseBasicType(symbol);
        if (_flag == -1) {
            throw new IllegalArgumentException("The sign(" + this.sign + ") is illegal");
        }
        String _clsName;
        if (sign.endsWith(Constants.SYMBOL_END)) {
            if (sign.contains(Constants.OBJECT_STRING)) {
                _flag |= MethodFlag.FLAG_JNI_METHOD_RETURN_STRING;
            } else {
                _flag |= MethodFlag.FLAG_JNI_METHOD_RETURN_OBJECT;
            }
            String descStr = Constants.SYMBOL_SQUARE_BRACKETS_LEFT + Constants.SYMBOL_L;
            _clsName = sign.substring(sign.lastIndexOf(descStr) + 2,
                    sign.length() - 1);
        } else {
            _clsName = String.valueOf(symbol);
        }
        this.arrayDimension = _arrayDimension;
        this.flag = _flag;
        this.clsName = _clsName;
    }

    private int parseBasicType(char symbol) {
        int flag = 0;
        switch (symbol) {
            case 'V':
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_VOID;
                break;
            case 'B':
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_BYTE;
                break;
            case 'C':
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_CHAR;
                break;
            case 'S':
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_SHORT;
                break;
            case 'I':
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_INT;
                break;
            case 'J':
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_LONG;
                break;
            case 'F':
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_FLOAT;
                break;
            case 'D':
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_DOUBLE;
                break;
            case 'Z':
                flag = MethodFlag.FLAG_JNI_METHOD_RETURN_BOOLEAN;
                break;
            case ';':
                break;
            default:
                flag = -1;
                break;
        }
        return flag;
    }
}
