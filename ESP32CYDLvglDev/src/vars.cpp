// #include "vars.h"

// // Number of flow global variables
// #define FLOW_GLOBAL_VARIABLES_COUNT 16

// // Storage used by EEZ runtime
// static float flow_global_variables[FLOW_GLOBAL_VARIABLES_COUNT];

// // ---------- Water level ----------
// float get_var_water_level() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_WATER_LEVEL];
// }

// void set_var_water_level(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_WATER_LEVEL] = value;
// }

// // ---------- Valve states ----------
// bool get_var_valve1_state() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_VALVE1_STATE] != 0.0f;
// }

// void set_var_valve1_state(bool value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_VALVE1_STATE] = value ? 1.0f : 0.0f;
// }

// bool get_var_valve2_state() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_VALVE2_STATE] != 0.0f;
// }

// void set_var_valve2_state(bool value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_VALVE2_STATE] = value ? 1.0f : 0.0f;
// }

// bool get_var_valve3_state() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_VALVE3_STATE] != 0.0f;
// }

// void set_var_valve3_state(bool value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_VALVE3_STATE] = value ? 1.0f : 0.0f;
// }

// // ---------- Pot 1 ----------
// float get_var_pot1_moisture() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT1_MOISTURE];
// }

// void set_var_pot1_moisture(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT1_MOISTURE] = value;
// }

// float get_var_pot1_temp() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT1_TEMP];
// }

// void set_var_pot1_temp(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT1_TEMP] = value;
// }

// float get_var_pot1_humidity() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT1_HUMIDITY];
// }

// void set_var_pot1_humidity(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT1_HUMIDITY] = value;
// }

// float get_var_pot1_vpd() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT1_VPD];
// }

// void set_var_pot1_vpd(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT1_VPD] = value;
// }

// // ---------- Pot 2 ----------
// float get_var_pot2_moisture() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT2_MOISTURE];
// }

// void set_var_pot2_moisture(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT2_MOISTURE] = value;
// }

// float get_var_pot2_temp() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT2_TEMP];
// }

// void set_var_pot2_temp(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT2_TEMP] = value;
// }

// float get_var_pot2_humidity() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT2_HUMIDITY];
// }

// void set_var_pot2_humidity(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT2_HUMIDITY] = value;
// }

// float get_var_pot2_vpd() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT2_VPD];
// }

// void set_var_pot2_vpd(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT2_VPD] = value;
// }

// // ---------- Pot 3 ----------
// float get_var_pot3_moisture() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT3_MOISTURE];
// }

// void set_var_pot3_moisture(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT3_MOISTURE] = value;
// }

// float get_var_pot3_temp() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT3_TEMP];
// }

// void set_var_pot3_temp(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT3_TEMP] = value;
// }

// float get_var_pot3_humidity() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT3_HUMIDITY];
// }

// void set_var_pot3_humidity(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT3_HUMIDITY] = value;
// }

// float get_var_pot3_vpd() {
//     return flow_global_variables[FLOW_GLOBAL_VARIABLE_POT3_VPD];
// }

// void set_var_pot3_vpd(float value) {
//     flow_global_variables[FLOW_GLOBAL_VARIABLE_POT3_VPD] = value;
// }