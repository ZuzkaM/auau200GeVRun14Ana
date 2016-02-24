#ifndef _cutsConsts_h_
#define _cutsConsts_h_

// # Original simulations (not using protons DCA and using old data driven MC)
  // ***********************************************
  // The original set of cuts:
  // ***********************************************
  // float MdLength = 0.003 + 0.004* index[0];
  // float MdcaDaughters = 0.02 - 0.004*index[1];
  // float MmaxVdist = 0.05 - 0.01*index[2];
  // float MpPt = 0.3 + 0.2*index[3];
  // float MpiPt = 0.3 + 0.2*index[4];
  // float MkPt = 0.3 + 0.2*index[5];
  // float McosTheta = 0.9825 + 0.0025*index[6];
  // ***********************************************

  // ***********************************************
  // second iteration:
  // ***********************************************
  // float MdLength = 0.012 + 0.004* index[0];
  // float MdcaDaughters = 0.018 - 0.002*index[1];
  // float MmaxVdist = 0.04 - 0.005*index[2];
  // float MpPt = 0.3 + 0.1*index[3];
  // float MpiPt = 0.3 + 0.1*index[4];
  // float MkPt = 0.3 + 0.1*index[5];
  // float McosTheta = 0.98 + 0.0025*index[6];
  // ***********************************************

  // ***********************************************
  // third iteration:
  // ***********************************************
  // float MdLength = 0.02 + 0.002* index[0];
  // float MdcaDaughters = 0.010 - 0.002*index[1];
  // float MmaxVdist = 0.028 - 0.002*index[2];
  // float MpPt = 0.6 + 0.1*index[3];
  // float MpiPt = 0.5 + 0.05*index[4];
  // float MkPt = 0.5 + 0.05*index[5];
  // float McosTheta = 0.9875 + 0.0025*index[6];
  // ***********************************************

  // ***********************************************
  // fourth iteration:
  // ***********************************************
  // float MdLength = 0.028 + 0.002* index[0];
  // float MdcaDaughters = 0.010 - 0.001*index[1];
  // float MmaxVdist = 0.025 - 0.001*index[2];
  // float MpPt = 1. + 0.1*index[3];
  // float MpiPt = 0.7 + 0.05*index[4];
  // float MkPt = 0.7 + 0.05*index[5];
  // float McosTheta = 0.995 + 0.001*index[6];
  // ***********************************************

  // ***********************************************
  // fifth iteration:
  // ***********************************************
  // float MdLength = 0.036 + 0.002* index[0];
  // float MdcaDaughters = 0.006 - 0.001*index[1];
  // float MmaxVdist = 0.021 - 0.001*index[2];
  // float MpPt = 1.4 + 0.1*index[3];
  // float MpiPt = 0.75 + 0.025*index[4];
  // float MkPt = 0.9 + 0.05*index[5];
  // float McosTheta = 0.998 + 0.0002*index[6];
  // ***********************************************

  // ***********************************************
  // sixth iteration:
  // ***********************************************
  // float MdLength = 0.028 + 0.002* index[0];
  // float MdcaDaughters = 0.006 - 0.0005*index[1];
  // float MmaxVdist = 0.025 - 0.001*index[2];
  // float MpPt = 1.8 + 0.1*index[3];
  // float MpiPt = 0.75 + 0.0125*index[4];
  // float MkPt = 1. + 0.025*index[5];
  // float McosTheta = 0.9988 + 0.0002*index[6];
  // ***********************************************

  // ***********************************************
  // seventh iteration:
  // ***********************************************
  // float MdLength = 0.034 + 0.001* index[0];
  // float MdcaDaughters = 0.0055 - 0.00025*index[1];
  // float MmaxVdist = 0.022 - 0.0005*index[2];
  // float MpPt = 1.7 + 0.05*index[3];
  // float MpiPt = 0.775 + 0.0125*index[4];
  // float MkPt = 1.0375 + 0.0125*index[5];
  // float McosTheta = 0.9986 + 0.0001*index[6];
  // ***********************************************

namespace firstIter
{
  const float DLstart = 0.003;
  const float DLinc = 0.01;
  const float dcaDaughtersStart = 0.02;
  const float dcaDaughtersInc = 0.005;
  const float maxVdistStart = 0.022;
  const float maxVdistInc = 0.0005;
  const float pPtStart = 0.2;
  const float pPtInc = 0.3;
  const float piPtStart = 0.2;
  const float piPtInc = 0.3;
  const float KPtStart = 0.2;
  const float KPtInc = 0.3;
  const float cosThetaStart = 0.98;
  const float cosThetaInc = 0.004;
}

#endif // #ifndef _cutsConsts_h_
