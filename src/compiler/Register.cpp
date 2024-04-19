//
// Created by Szenes Márton on 2024. 03. 14..
//
#include <algorithm>
#include "../../include/compiler/Register.h"

Register::Register() = default; //: value(0) { }

Register::Register(const string& name, float defValue) : name(name), value(defValue) { }

Register::~Register() = default;


