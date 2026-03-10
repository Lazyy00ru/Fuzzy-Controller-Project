#include <algorithm>
#include "fuzzylogic.h"

void initFuzzyRules(fuzzy_system_rec *fl) {
    // TRUE 2-INPUT FUZZY SYSTEM
    // 25 rules covering all combinations of angle (INPUT_X) and position (INPUT_Y)
    // Rule structure: IF angle is X AND position is Y THEN force is Z

    int rule_idx = 0;

    // Row 1: Angle = Negative Large (in_nl)
    // When tilted far left, apply strong right force, modified by position
    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_nl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_nl;  // Far left + far left position
    fl->rules[rule_idx].out_fuzzy_set = out_pvl;   // Maximum right force
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_nl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ns;
    fl->rules[rule_idx].out_fuzzy_set = out_pvl;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_nl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ze;
    fl->rules[rule_idx].out_fuzzy_set = out_pvl;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_nl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ps;
    fl->rules[rule_idx].out_fuzzy_set = out_pl;    // Slightly reduced since position is right
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_nl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_pl;  // Angle left but position far right
    fl->rules[rule_idx].out_fuzzy_set = out_pm;    // Moderate force (conflicting objectives)
    rule_idx++;

    // Row 2: Angle = Negative Small (in_ns)
    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ns;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_nl;
    fl->rules[rule_idx].out_fuzzy_set = out_pl;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ns;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ns;
    fl->rules[rule_idx].out_fuzzy_set = out_pl;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ns;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ze;
    fl->rules[rule_idx].out_fuzzy_set = out_pm;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ns;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ps;
    fl->rules[rule_idx].out_fuzzy_set = out_ps;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ns;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_pl;  // Angle slightly left but position far right
    fl->rules[rule_idx].out_fuzzy_set = out_ze;    // Conflicting - use minimal force
    rule_idx++;

    // Row 3: Angle = Zero (in_ze)
    // When balanced, focus primarily on position control
    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ze;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_nl;  // Balanced angle but far left
    fl->rules[rule_idx].out_fuzzy_set = out_pl;    // Push right to center
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ze;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ns;
    fl->rules[rule_idx].out_fuzzy_set = out_pm;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ze;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ze;  // Perfect balance
    fl->rules[rule_idx].out_fuzzy_set = out_ze;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ze;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ps;
    fl->rules[rule_idx].out_fuzzy_set = out_nm;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ze;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_pl;  // Balanced angle but far right
    fl->rules[rule_idx].out_fuzzy_set = out_nl;    // Push left to center
    rule_idx++;

    // Row 4: Angle = Positive Small (in_ps)
    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ps;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_nl;  // Angle slightly right but position far left
    fl->rules[rule_idx].out_fuzzy_set = out_ze;    // Conflicting - use minimal force
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ps;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ns;
    fl->rules[rule_idx].out_fuzzy_set = out_ns;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ps;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ze;
    fl->rules[rule_idx].out_fuzzy_set = out_nm;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ps;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ps;
    fl->rules[rule_idx].out_fuzzy_set = out_nl;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_ps;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_pl;
    fl->rules[rule_idx].out_fuzzy_set = out_nl;
    rule_idx++;

    // Row 5: Angle = Positive Large (in_pl)
    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_pl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_nl;  // Angle far right but position far left
    fl->rules[rule_idx].out_fuzzy_set = out_nm;    // Conflicting - moderate force
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_pl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ns;
    fl->rules[rule_idx].out_fuzzy_set = out_nl;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_pl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ze;
    fl->rules[rule_idx].out_fuzzy_set = out_nvl;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_pl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_ps;
    fl->rules[rule_idx].out_fuzzy_set = out_nvl;
    rule_idx++;

    fl->rules[rule_idx].inp_index[0] = INPUT_X;
    fl->rules[rule_idx].inp_fuzzy_set[0] = in_pl;
    fl->rules[rule_idx].inp_index[1] = INPUT_Y;
    fl->rules[rule_idx].inp_fuzzy_set[1] = in_pl;  // Both angle and position far right
    fl->rules[rule_idx].out_fuzzy_set = out_nvl;   // Maximum left force
    rule_idx++;
}

void initMembershipFunctions(fuzzy_system_rec *fl) {
    // Input X fuzzy sets - angle control
    // OPTIMIZED FOR WIDER ANGLE RANGE (±30 degrees)
    // Key insight: Need wider membership functions to capture larger angles

    fl->inp_mem_fns[INPUT_X][in_nl] = init_trapz(-100.0, -6.0, -100.0, -6.0, left_trapezoid);
    fl->inp_mem_fns[INPUT_X][in_ns] = init_trapz(-9.0, -4.0, -1.5, -0.3, regular_trapezoid);
    fl->inp_mem_fns[INPUT_X][in_ze] = init_trapz(-2.5, -0.5, 0.5, 2.5, regular_trapezoid);
    fl->inp_mem_fns[INPUT_X][in_ps] = init_trapz(0.3, 1.5, 4.0, 9.0, regular_trapezoid);
    fl->inp_mem_fns[INPUT_X][in_pl] = init_trapz(6.0, 100.0, 6.0, 100.0, right_trapezoid);

    // Input Y fuzzy sets - position control (cart position)
    // Keep these similar to original - position control is still important
    fl->inp_mem_fns[INPUT_Y][in_nl] = init_trapz(-50.0, -0.8, -50.0, -0.8, left_trapezoid);
    fl->inp_mem_fns[INPUT_Y][in_ns] = init_trapz(-1.2, -0.5, -0.12, 0.0, regular_trapezoid);
    fl->inp_mem_fns[INPUT_Y][in_ze] = init_trapz(-0.3, -0.05, 0.05, 0.3, regular_trapezoid);
    fl->inp_mem_fns[INPUT_Y][in_ps] = init_trapz(0.0, 0.12, 0.5, 1.2, regular_trapezoid);
    fl->inp_mem_fns[INPUT_Y][in_pl] = init_trapz(0.8, 50.0, 0.8, 50.0, right_trapezoid);
}

void initFuzzySystem (fuzzy_system_rec *fl) {
    fl->no_of_inputs = 2;  // Using both angle and position inputs
    fl->no_of_rules = 25;
    fl->no_of_inp_regions = 5;
    fl->no_of_outputs = 9;

    // OPTIMIZED FOR 15-30 DEGREE RANGE
    // Strategy: Increase angle response while maintaining adequate damping
    // and position control to prevent boundary violations

   coefficient_A = 18.0;
   coefficient_B = 9.5;
   coefficient_C = 5.0;  // Stronger position control
   coefficient_D = 4.0;  // Stronger velocity damping

    // Output forces - Increased moderately for larger angles
    // Still within reasonable range and not hitting the ±80 clamp too often
    fl->output_values[out_nvl] = -145;  // Increased from -127
    fl->output_values[out_nl]  = -105;  // Increased from -92
    fl->output_values[out_nm]  = -68;   // Increased from -59
    fl->output_values[out_ns]  = -32;   // Increased from -27
    fl->output_values[out_ze]  = 0;
    fl->output_values[out_ps]  = 32;
    fl->output_values[out_pm]  = 68;
    fl->output_values[out_pl]  = 105;
    fl->output_values[out_pvl] = 145;

    fl->rules = (rule*) malloc(fl->no_of_rules * sizeof(rule));
    fl->allocated = true;
    initFuzzyRules(fl);
    initMembershipFunctions(fl);
}

trapezoid init_trapz (float x1,float x2,float x3,float x4, trapz_type typ) {
   trapezoid trz;
   trz.a = x1; trz.b = x2; trz.c = x3; trz.d = x4; trz.tp = typ;
   switch (trz.tp) {
      case regular_trapezoid: trz.l_slope = 1.0/(trz.b - trz.a); trz.r_slope = 1.0/(trz.c - trz.d); break;
      case left_trapezoid: trz.r_slope = 1.0/(trz.a - trz.b); trz.l_slope = 0.0; break;
      case right_trapezoid: trz.l_slope = 1.0/(trz.b - trz.a); trz.r_slope = 0.0; break;
   }
   return trz;
}

float trapz (float x, trapezoid trz) {
   switch (trz.tp) {
      case left_trapezoid: if (x <= trz.a) return 1.0; if (x >= trz.b) return 0.0; return trz.r_slope * (x - trz.b);
      case right_trapezoid: if (x <= trz.a) return 0.0; if (x >= trz.b) return 1.0; return trz.l_slope * (x - trz.a);
      case regular_trapezoid:
         if ((x <= trz.a) || (x >= trz.d)) return 0.0;
         if ((x >= trz.b) && (x <= trz.c)) return 1.0;
         if ((x >= trz.a) && (x <= trz.b)) return trz.l_slope * (x - trz.a);
         if ((x >= trz.c) && (x <= trz.d)) return trz.r_slope * (x - trz.d);
   }
   return 0.0;
}

float min_of(float values[],int no_of_inps) {
   float val = values[0];
   for (int i = 1; i < no_of_inps; i++) { if (values[i] < val) val = values[i]; }
   return val;
}

float fuzzy_system (float inputs[],fuzzy_system_rec fz) {
   int i,j; short variable_index,fuzzy_set;
   float sum1 = 0.0,sum2 = 0.0,weight; float m_values[MAX_NO_OF_INPUTS];
   for (i = 0;i < fz.no_of_rules;i++) {
      for (j = 0;j < fz.no_of_inputs;j++) {
	   variable_index = fz.rules[i].inp_index[j]; fuzzy_set = fz.rules[i].inp_fuzzy_set[j];
	   m_values[j] = trapz(inputs[variable_index], fz.inp_mem_fns[variable_index][fuzzy_set]);
	   }
       weight = min_of(m_values,fz.no_of_inputs);
       sum1 += weight * fz.output_values[fz.rules[i].out_fuzzy_set]; sum2 += weight;
   }
	if (fabs(sum2) < TOO_SMALL) {
      cout << "\r\nFLPRCS Error: Sum2 in fuzzy_system is 0." << endl;
      cout << "INPUT_X = " << inputs[INPUT_X] << ", INPUT_Y = " << inputs[INPUT_Y] << endl;
      return 0.0;
   }
   return (sum1/sum2);
}

void free_fuzzy_rules (fuzzy_system_rec *fz) {
   if (fz->allocated){ free (fz->rules); }
   fz->allocated = false;
}