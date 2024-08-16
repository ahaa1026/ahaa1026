/*
 * File: PID_MATLAB.h
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

#ifndef RTW_HEADER_PID_MATLAB_h_
#define RTW_HEADER_PID_MATLAB_h_
#include <math.h>
#include "STM32_Config.h"
#include "PID_MATLAB_External_Functions.h"
#ifndef PID_MATLAB_COMMON_INCLUDES_
# define PID_MATLAB_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* PID_MATLAB_COMMON_INCLUDES_ */

#include "PID_MATLAB_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T FilterDifferentiatorTF_states;/* '<S30>/Filter Differentiator TF' */
  real_T Integrator_DSTATE;            /* '<S37>/Integrator' */
  real_T UD_DSTATE;                    /* '<S1>/UD' */
  real_T FilterDifferentiatorTF_states_b;/* '<S80>/Filter Differentiator TF' */
  real_T Integrator_DSTATE_p;          /* '<S87>/Integrator' */
} DW_PID_MATLAB;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T P_P;                          /* '<Root>/P_P' */
  real_T P_I;                          /* '<Root>/P_I' */
  real_T P_D;                          /* '<Root>/P_D' */
  real_T V_N;                          /* '<Root>/V_N' */
  real_T V_D;                          /* '<Root>/V_D' */
  real_T V_P;                          /* '<Root>/V_P' */
  real_T P_TARGET;                     /* '<Root>/P_TARGET' */
  real_T P_FEED;                       /* '<Root>/P_FEED' */
  real_T P_FEED1;                      /* '<Root>/P_FEED1' */
  real_T P_P2;                         /* '<Root>/P_P2' */
  real_T P_N;                          /* '<Root>/P_N' */
  real_T V_I;                          /* '<Root>/V_I' */
} ExtU_PID_MATLAB;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Current;                      /* '<Root>/Current' */
} ExtY_PID_MATLAB;

/* Real-time Model Data Structure */
struct tag_RTM_PID_MATLAB {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block states (default storage) */
extern DW_PID_MATLAB PID_MATLAB_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_PID_MATLAB PID_MATLAB_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_PID_MATLAB PID_MATLAB_Y;

/* Model entry point functions */
extern void PID_MATLAB_initialize(void);
extern void PID_MATLAB_step(void);

/* Real-time Model object */
extern RT_MODEL_PID_MATLAB *const PID_MATLAB_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Data Type Duplicate' : Unused code path elimination
 * Block '<S30>/Passthrough for tuning' : Eliminate redundant data type conversion
 * Block '<S80>/Passthrough for tuning' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PID_MATLAB'
 * '<S1>'   : 'PID_MATLAB/Discrete Derivative'
 * '<S2>'   : 'PID_MATLAB/POS_PID'
 * '<S3>'   : 'PID_MATLAB/VEC_PID'
 * '<S4>'   : 'PID_MATLAB/POS_PID/Anti-windup'
 * '<S5>'   : 'PID_MATLAB/POS_PID/D Gain'
 * '<S6>'   : 'PID_MATLAB/POS_PID/Filter'
 * '<S7>'   : 'PID_MATLAB/POS_PID/Filter ICs'
 * '<S8>'   : 'PID_MATLAB/POS_PID/I Gain'
 * '<S9>'   : 'PID_MATLAB/POS_PID/Ideal P Gain'
 * '<S10>'  : 'PID_MATLAB/POS_PID/Ideal P Gain Fdbk'
 * '<S11>'  : 'PID_MATLAB/POS_PID/Integrator'
 * '<S12>'  : 'PID_MATLAB/POS_PID/Integrator ICs'
 * '<S13>'  : 'PID_MATLAB/POS_PID/N Copy'
 * '<S14>'  : 'PID_MATLAB/POS_PID/N Gain'
 * '<S15>'  : 'PID_MATLAB/POS_PID/P Copy'
 * '<S16>'  : 'PID_MATLAB/POS_PID/Parallel P Gain'
 * '<S17>'  : 'PID_MATLAB/POS_PID/Reset Signal'
 * '<S18>'  : 'PID_MATLAB/POS_PID/Saturation'
 * '<S19>'  : 'PID_MATLAB/POS_PID/Saturation Fdbk'
 * '<S20>'  : 'PID_MATLAB/POS_PID/Sum'
 * '<S21>'  : 'PID_MATLAB/POS_PID/Sum Fdbk'
 * '<S22>'  : 'PID_MATLAB/POS_PID/Tracking Mode'
 * '<S23>'  : 'PID_MATLAB/POS_PID/Tracking Mode Sum'
 * '<S24>'  : 'PID_MATLAB/POS_PID/Tsamp - Integral'
 * '<S25>'  : 'PID_MATLAB/POS_PID/Tsamp - Ngain'
 * '<S26>'  : 'PID_MATLAB/POS_PID/postSat Signal'
 * '<S27>'  : 'PID_MATLAB/POS_PID/preSat Signal'
 * '<S28>'  : 'PID_MATLAB/POS_PID/Anti-windup/Disc. Clamping Parallel'
 * '<S29>'  : 'PID_MATLAB/POS_PID/D Gain/External Parameters'
 * '<S30>'  : 'PID_MATLAB/POS_PID/Filter/Disc. Trapezoidal Filter'
 * '<S31>'  : 'PID_MATLAB/POS_PID/Filter/Disc. Trapezoidal Filter/Tsamp'
 * '<S32>'  : 'PID_MATLAB/POS_PID/Filter/Disc. Trapezoidal Filter/Tsamp/Internal Ts'
 * '<S33>'  : 'PID_MATLAB/POS_PID/Filter ICs/Internal IC - Filter'
 * '<S34>'  : 'PID_MATLAB/POS_PID/I Gain/External Parameters'
 * '<S35>'  : 'PID_MATLAB/POS_PID/Ideal P Gain/Passthrough'
 * '<S36>'  : 'PID_MATLAB/POS_PID/Ideal P Gain Fdbk/Passthrough'
 * '<S37>'  : 'PID_MATLAB/POS_PID/Integrator/Discrete'
 * '<S38>'  : 'PID_MATLAB/POS_PID/Integrator ICs/Internal IC'
 * '<S39>'  : 'PID_MATLAB/POS_PID/N Copy/External Parameters'
 * '<S40>'  : 'PID_MATLAB/POS_PID/N Gain/External Parameters'
 * '<S41>'  : 'PID_MATLAB/POS_PID/P Copy/Disabled'
 * '<S42>'  : 'PID_MATLAB/POS_PID/Parallel P Gain/External Parameters'
 * '<S43>'  : 'PID_MATLAB/POS_PID/Reset Signal/Disabled'
 * '<S44>'  : 'PID_MATLAB/POS_PID/Saturation/Enabled'
 * '<S45>'  : 'PID_MATLAB/POS_PID/Saturation Fdbk/Passthrough'
 * '<S46>'  : 'PID_MATLAB/POS_PID/Sum/Sum_PID'
 * '<S47>'  : 'PID_MATLAB/POS_PID/Sum Fdbk/Enabled'
 * '<S48>'  : 'PID_MATLAB/POS_PID/Tracking Mode/Disabled'
 * '<S49>'  : 'PID_MATLAB/POS_PID/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'PID_MATLAB/POS_PID/Tsamp - Integral/Passthrough'
 * '<S51>'  : 'PID_MATLAB/POS_PID/Tsamp - Ngain/Passthrough'
 * '<S52>'  : 'PID_MATLAB/POS_PID/postSat Signal/Feedback_Path'
 * '<S53>'  : 'PID_MATLAB/POS_PID/preSat Signal/Feedback_Path'
 * '<S54>'  : 'PID_MATLAB/VEC_PID/Anti-windup'
 * '<S55>'  : 'PID_MATLAB/VEC_PID/D Gain'
 * '<S56>'  : 'PID_MATLAB/VEC_PID/Filter'
 * '<S57>'  : 'PID_MATLAB/VEC_PID/Filter ICs'
 * '<S58>'  : 'PID_MATLAB/VEC_PID/I Gain'
 * '<S59>'  : 'PID_MATLAB/VEC_PID/Ideal P Gain'
 * '<S60>'  : 'PID_MATLAB/VEC_PID/Ideal P Gain Fdbk'
 * '<S61>'  : 'PID_MATLAB/VEC_PID/Integrator'
 * '<S62>'  : 'PID_MATLAB/VEC_PID/Integrator ICs'
 * '<S63>'  : 'PID_MATLAB/VEC_PID/N Copy'
 * '<S64>'  : 'PID_MATLAB/VEC_PID/N Gain'
 * '<S65>'  : 'PID_MATLAB/VEC_PID/P Copy'
 * '<S66>'  : 'PID_MATLAB/VEC_PID/Parallel P Gain'
 * '<S67>'  : 'PID_MATLAB/VEC_PID/Reset Signal'
 * '<S68>'  : 'PID_MATLAB/VEC_PID/Saturation'
 * '<S69>'  : 'PID_MATLAB/VEC_PID/Saturation Fdbk'
 * '<S70>'  : 'PID_MATLAB/VEC_PID/Sum'
 * '<S71>'  : 'PID_MATLAB/VEC_PID/Sum Fdbk'
 * '<S72>'  : 'PID_MATLAB/VEC_PID/Tracking Mode'
 * '<S73>'  : 'PID_MATLAB/VEC_PID/Tracking Mode Sum'
 * '<S74>'  : 'PID_MATLAB/VEC_PID/Tsamp - Integral'
 * '<S75>'  : 'PID_MATLAB/VEC_PID/Tsamp - Ngain'
 * '<S76>'  : 'PID_MATLAB/VEC_PID/postSat Signal'
 * '<S77>'  : 'PID_MATLAB/VEC_PID/preSat Signal'
 * '<S78>'  : 'PID_MATLAB/VEC_PID/Anti-windup/Disc. Clamping Parallel'
 * '<S79>'  : 'PID_MATLAB/VEC_PID/D Gain/External Parameters'
 * '<S80>'  : 'PID_MATLAB/VEC_PID/Filter/Disc. Trapezoidal Filter'
 * '<S81>'  : 'PID_MATLAB/VEC_PID/Filter/Disc. Trapezoidal Filter/Tsamp'
 * '<S82>'  : 'PID_MATLAB/VEC_PID/Filter/Disc. Trapezoidal Filter/Tsamp/Internal Ts'
 * '<S83>'  : 'PID_MATLAB/VEC_PID/Filter ICs/Internal IC - Filter'
 * '<S84>'  : 'PID_MATLAB/VEC_PID/I Gain/External Parameters'
 * '<S85>'  : 'PID_MATLAB/VEC_PID/Ideal P Gain/Passthrough'
 * '<S86>'  : 'PID_MATLAB/VEC_PID/Ideal P Gain Fdbk/Passthrough'
 * '<S87>'  : 'PID_MATLAB/VEC_PID/Integrator/Discrete'
 * '<S88>'  : 'PID_MATLAB/VEC_PID/Integrator ICs/Internal IC'
 * '<S89>'  : 'PID_MATLAB/VEC_PID/N Copy/External Parameters'
 * '<S90>'  : 'PID_MATLAB/VEC_PID/N Gain/External Parameters'
 * '<S91>'  : 'PID_MATLAB/VEC_PID/P Copy/Disabled'
 * '<S92>'  : 'PID_MATLAB/VEC_PID/Parallel P Gain/External Parameters'
 * '<S93>'  : 'PID_MATLAB/VEC_PID/Reset Signal/Disabled'
 * '<S94>'  : 'PID_MATLAB/VEC_PID/Saturation/Enabled'
 * '<S95>'  : 'PID_MATLAB/VEC_PID/Saturation Fdbk/Passthrough'
 * '<S96>'  : 'PID_MATLAB/VEC_PID/Sum/Sum_PID'
 * '<S97>'  : 'PID_MATLAB/VEC_PID/Sum Fdbk/Enabled'
 * '<S98>'  : 'PID_MATLAB/VEC_PID/Tracking Mode/Disabled'
 * '<S99>'  : 'PID_MATLAB/VEC_PID/Tracking Mode Sum/Passthrough'
 * '<S100>' : 'PID_MATLAB/VEC_PID/Tsamp - Integral/Passthrough'
 * '<S101>' : 'PID_MATLAB/VEC_PID/Tsamp - Ngain/Passthrough'
 * '<S102>' : 'PID_MATLAB/VEC_PID/postSat Signal/Feedback_Path'
 * '<S103>' : 'PID_MATLAB/VEC_PID/preSat Signal/Feedback_Path'
 */
#endif                                 /* RTW_HEADER_PID_MATLAB_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] PID_MATLAB.h
 */
