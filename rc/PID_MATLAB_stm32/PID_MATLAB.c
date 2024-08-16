/*
 * File: PID_MATLAB.c
 *
 * Code generated for Simulink model :PID_MATLAB.
 *
 * Model version      : 1.0
 * Simulink Coder version    : 9.3 (R2020a) 18-Nov-2019
 * TLC version       : 9.3 (Jan 23 2020)
 * C/C++ source code generated on  : Tue Aug 13 02:03:56 2024
 *
 * Target selection: stm32.tlc
 * Embedded hardware selection: STM32CortexM
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 *
 *
 * ******************************************************************************
 * * attention
 * *
 * * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * *
 * ******************************************************************************
 */

#include "PID_MATLAB.h"
#include "drv_can.h"
#include "PID_MATLAB_private.h"

/* Block states (default storage) */
DW_PID_MATLAB PID_MATLAB_DW;

/* External inputs (root inport signals with default storage) */
ExtU_PID_MATLAB PID_MATLAB_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_PID_MATLAB PID_MATLAB_Y;

/* Real-time model */
RT_MODEL_PID_MATLAB PID_MATLAB_M_;
RT_MODEL_PID_MATLAB *const PID_MATLAB_M = &PID_MATLAB_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (PID_MATLAB_M->Timing.TaskCounters.TID[1])++;
  if ((PID_MATLAB_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [0.005s, 0.0s] */
    PID_MATLAB_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void PID_MATLAB_step(void)
{
  real_T denAccum;
  real_T denAccum_0;
  real_T rtb_SignPreIntegrator;
  real_T rtb_NProdOut;
  real_T rtb_IProdOut;
  real_T rtb_ZeroGain;
  boolean_T rtb_NotEqual;
  real_T rtb_TSamp;
  real_T rtb_ZeroGain_b;
  real_T Integrator;
  real_T tmp;
  if (PID_MATLAB_M->Timing.TaskCounters.TID[1] == 0) {
    rtb_SignPreIntegrator = PID_MATLAB_U.P_TARGET - PID_MATLAB_U.P_FEED;
    rtb_NProdOut = rtb_SignPreIntegrator * PID_MATLAB_U.P_P;
    PID_MATLAB_Y.Current = PID_MATLAB_U.P_N * 0.0025;
    rtb_IProdOut = 1.0 / (PID_MATLAB_Y.Current + 1.0);
    denAccum = rtb_SignPreIntegrator * PID_MATLAB_U.P_D - (PID_MATLAB_Y.Current
      - 1.0) * rtb_IProdOut * PID_MATLAB_DW.FilterDifferentiatorTF_states;
    rtb_IProdOut = (denAccum + -PID_MATLAB_DW.FilterDifferentiatorTF_states) *
      rtb_IProdOut * PID_MATLAB_U.P_N;
    PID_MATLAB_Y.Current = (rtb_NProdOut + PID_MATLAB_DW.Integrator_DSTATE) +
      rtb_IProdOut;
    rtb_ZeroGain = 0.0 * PID_MATLAB_Y.Current;
    if (PID_MATLAB_Y.Current > 300.0) {
      PID_MATLAB_Y.Current -= 300.0;
    } else if (PID_MATLAB_Y.Current >= -300.0) {
      PID_MATLAB_Y.Current = 0.0;
    } else {
      PID_MATLAB_Y.Current -= -300.0;
    }

    rtb_NotEqual = (rtb_ZeroGain != PID_MATLAB_Y.Current);
    if (PID_MATLAB_Y.Current < 0.0) {
      PID_MATLAB_Y.Current = -1.0;
    } else if (PID_MATLAB_Y.Current > 0.0) {
      PID_MATLAB_Y.Current = 1.0;
    } else if (PID_MATLAB_Y.Current == 0.0) {
      PID_MATLAB_Y.Current = 0.0;
    } else {
      PID_MATLAB_Y.Current = (rtNaN);
    }

    rtb_SignPreIntegrator *= PID_MATLAB_U.P_I;
    if (rtIsNaN(PID_MATLAB_Y.Current)) {
      rtb_ZeroGain_b = 0.0;
    } else {
      rtb_ZeroGain_b = fmod(PID_MATLAB_Y.Current, 256.0);
    }

    if (rtb_SignPreIntegrator < 0.0) {
      tmp = -1.0;
    } else if (rtb_SignPreIntegrator > 0.0) {
      tmp = 1.0;
    } else if (rtb_SignPreIntegrator == 0.0) {
      tmp = 0.0;
    } else {
      tmp = (rtNaN);
    }

    if (rtIsNaN(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 256.0);
    }

    if (rtb_NotEqual && ((rtb_ZeroGain_b < 0.0 ? (int32_T)(int8_T)-(int8_T)
                          (uint8_T)-rtb_ZeroGain_b : (int32_T)(int8_T)(uint8_T)
                          rtb_ZeroGain_b) == (tmp < 0.0 ? (int32_T)(int8_T)
          -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp))) {
      rtb_ZeroGain = 0.0;
    } else {
      rtb_ZeroGain = rtb_SignPreIntegrator;
    }

    Integrator = 0.0025 * rtb_ZeroGain + PID_MATLAB_DW.Integrator_DSTATE;
    rtb_NProdOut = (rtb_NProdOut + Integrator) + rtb_IProdOut;
    if (rtb_NProdOut > 300.0) {
      rtb_NProdOut = 300.0;
    } else {
      if (rtb_NProdOut < -300.0) {
        rtb_NProdOut = -300.0;
      }
    }

    rtb_TSamp = PID_MATLAB_U.P_P2 * PID_MATLAB_U.P_TARGET * 200.0;
    rtb_IProdOut = (rtb_NProdOut - PID_MATLAB_U.P_FEED1) + (rtb_TSamp -
      PID_MATLAB_DW.UD_DSTATE);
    PID_MATLAB_Y.Current = rtb_IProdOut * PID_MATLAB_U.V_P;
    rtb_NProdOut = PID_MATLAB_U.V_N * 0.0025;
    rtb_SignPreIntegrator = 1.0 / (rtb_NProdOut + 1.0);
    denAccum_0 = rtb_IProdOut * PID_MATLAB_U.V_D - (rtb_NProdOut - 1.0) *
      rtb_SignPreIntegrator * PID_MATLAB_DW.FilterDifferentiatorTF_states_b;
    rtb_NProdOut = (denAccum_0 + -PID_MATLAB_DW.FilterDifferentiatorTF_states_b)
      * rtb_SignPreIntegrator * PID_MATLAB_U.V_N;
    rtb_SignPreIntegrator = (PID_MATLAB_Y.Current +
      PID_MATLAB_DW.Integrator_DSTATE_p) + rtb_NProdOut;
    rtb_ZeroGain_b = 0.0 * rtb_SignPreIntegrator;
    if (rtb_SignPreIntegrator > 25000.0) {
      rtb_SignPreIntegrator -= 25000.0;
    } else if (rtb_SignPreIntegrator >= -25000.0) {
      rtb_SignPreIntegrator = 0.0;
    } else {
      rtb_SignPreIntegrator -= -25000.0;
    }

    rtb_NotEqual = (rtb_ZeroGain_b != rtb_SignPreIntegrator);
    if (rtb_SignPreIntegrator < 0.0) {
      rtb_SignPreIntegrator = -1.0;
    } else if (rtb_SignPreIntegrator > 0.0) {
      rtb_SignPreIntegrator = 1.0;
    } else if (rtb_SignPreIntegrator == 0.0) {
      rtb_SignPreIntegrator = 0.0;
    } else {
      rtb_SignPreIntegrator = (rtNaN);
    }

    rtb_IProdOut *= PID_MATLAB_U.V_I;
    if (rtIsNaN(rtb_SignPreIntegrator)) {
      rtb_ZeroGain_b = 0.0;
    } else {
      rtb_ZeroGain_b = fmod(rtb_SignPreIntegrator, 256.0);
    }

    if (rtb_IProdOut < 0.0) {
      tmp = -1.0;
    } else if (rtb_IProdOut > 0.0) {
      tmp = 1.0;
    } else if (rtb_IProdOut == 0.0) {
      tmp = 0.0;
    } else {
      tmp = (rtNaN);
    }

    if (rtIsNaN(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 256.0);
    }

    if (rtb_NotEqual && ((rtb_ZeroGain_b < 0.0 ? (int32_T)(int8_T)-(int8_T)
                          (uint8_T)-rtb_ZeroGain_b : (int32_T)(int8_T)(uint8_T)
                          rtb_ZeroGain_b) == (tmp < 0.0 ? (int32_T)(int8_T)
          -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp))) {
      rtb_IProdOut = 0.0;
    }

    rtb_SignPreIntegrator = 0.0025 * rtb_IProdOut +
      PID_MATLAB_DW.Integrator_DSTATE_p;
    PID_MATLAB_Y.Current = (PID_MATLAB_Y.Current + rtb_SignPreIntegrator) +
      rtb_NProdOut;
    if (PID_MATLAB_Y.Current > 25000.0) {
      PID_MATLAB_Y.Current = 25000.0;
    } else {
      if (PID_MATLAB_Y.Current < -25000.0) {
        PID_MATLAB_Y.Current = -25000.0;
      }
    }

    PID_MATLAB_DW.FilterDifferentiatorTF_states = denAccum;
    PID_MATLAB_DW.Integrator_DSTATE = 0.0025 * rtb_ZeroGain + Integrator;
    PID_MATLAB_DW.UD_DSTATE = rtb_TSamp;
    PID_MATLAB_DW.FilterDifferentiatorTF_states_b = denAccum_0;
    PID_MATLAB_DW.Integrator_DSTATE_p = 0.0025 * rtb_IProdOut +
      rtb_SignPreIntegrator;
  }

  rate_scheduler();
}

/* Model initialize function */
void PID_MATLAB_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

 // CAN_SendCurrent(0,0,0,0);

}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] PID_MATLAB.c
 */
