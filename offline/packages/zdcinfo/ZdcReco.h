// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef ZDCRECO_H
#define ZDCRECO_H

//===========================================================
/// \author Ejiro Umaka
//===========================================================

#include <fun4all/SubsysReco.h>
#include <cdbobjects/CDBTTree.h>
#include <string>  // for string
#include <vector>  // for vector

class PHCompositeNode;
class Zdcinfo;

class ZdcReco : public SubsysReco
{
 public:
   ZdcReco(const std::string &name = "ZdcReco");
  ~ZdcReco() override = default;
  int InitRun(PHCompositeNode *topNode) override;
  int process_event(PHCompositeNode *topNode) override;
  int End(PHCompositeNode * /*topNode*/) override;
  void ResetMe();
  void set_zdc1_cut(const float &f)
  {
    _zdc1_e = f;
  }
  void set_zdc2_cut(const float &g)
  {
    _zdc2_e = g;
  }
  
 private:
   void CompSmdPos();
   CDBTTree *cdbttree{ nullptr};
   Zdcinfo *m_zdcinfo{nullptr};
   std::string m_Detector = "ZDC"; 
   std::string m_fieldname;
   std::string m_calibName;
   bool m_overrideCalibName{false};
   bool m_overrideFieldName{false};
   std::vector<float> vsmdadc;
   std::vector<float> vsmdtime;
   std::vector<float> vzdcadc;
   std::vector<float> vzdctime;
   float smd_adc[32] = {0.0f};
   float smd_pos[4] = {0.0f};
   float radius_south{0.};
   float radius_north{0.};
   float _sumS{0.};
   float _sumN{0.};
   float _zdc1_e{65.0};
   float _zdc2_e{20.0};
};

#endif  // ZDCRECO_H
