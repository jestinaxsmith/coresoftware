// Tell emacs that this is a C++ source
// -*- C++ -*-.
#ifndef G4MVTX_PHG4MVTXDETECTOR_H
#define G4MVTX_PHG4MVTXDETECTOR_H

#include <trackbase/TrkrDefs.h>

#include <g4main/PHG4Detector.h>

#include <array>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

class G4AssemblyVolume;
class G4LogicalVolume;
class G4VPhysicalVolume;
class PHCompositeNode;
class PHG4MvtxDisplayAction;
class PHG4Subsystem;
class PHParametersContainer;
class PHG4MvtxMisalignment;

class PHG4MvtxDetector : public PHG4Detector
{
 public:
  //! constructor
  PHG4MvtxDetector(PHG4Subsystem* subsys, PHCompositeNode* Node, const PHParametersContainer* _paramsContainer, const std::string& dnam,
                   const bool applyMisalignment, const std::string& misalignmentfile);

  //! destructor
  ~PHG4MvtxDetector() override {}

  //! construct
  void ConstructMe(G4LogicalVolume* world) override;

  //!@name volume accessors
  //@{
  int IsInMvtx(G4VPhysicalVolume*, int& layer, int& stave) const;
  int IsSensor(G4VPhysicalVolume*) const;
  //@}

  int IsActive(int lyr) const { return m_IsLayerActive[lyr]; }
  int IsSupportActive(int lyr) const { return m_IsLayerSupportActive[lyr]; }
  int IsBlackHole(int lyr) const { return m_IsBlackHole[lyr]; }
  void SuperDetector(const std::string& name) { m_SuperDetector = name; }
  const std::string &SuperDetector() const { return m_SuperDetector; }
  void Detector(const std::string& name) { m_Detector = name; }
  const std::string &Detector() const { return m_Detector; }

  int get_layer(int stv_index) const;
  int get_stave(int stv_index) const;

  void FillSupportLVArray(G4LogicalVolume* lv) { m_SupportLV.insert(lv); }

  void ApplyMisalignment(bool b) { apply_misalignment = b; };

 private:
  void AddGeometryNode();
  int ConstructMvtx(G4LogicalVolume* sandwich);
  int ConstructMvtx_Layer(int layer, G4AssemblyVolume* stave, G4LogicalVolume*& trackerenvelope);
  int ConstructMvtxPassiveVol(G4LogicalVolume*& lv);

  void SetDisplayProperty(G4AssemblyVolume* av);
  void SetDisplayProperty(G4LogicalVolume* lv);
  void FillPVArray(G4AssemblyVolume* av);
  void FindSensor(G4LogicalVolume* lv);
  // calculated quantities
  double get_phistep(int lay) const { return 2.0 * M_PI / m_N_staves[lay]; }

  PHG4MvtxDisplayAction* m_DisplayAction{nullptr};
  const PHParametersContainer* m_ParamsContainer{nullptr};

  static constexpr int n_Layers{3};
  int m_SupportActiveFlag{0};

  std::string m_Detector;
  std::string m_SuperDetector;
  std::string m_StaveGeometryFile;

  // map of sensor physical volume pointers
  std::set<G4VPhysicalVolume*> m_SensorPV;
  std::map<G4VPhysicalVolume*, std::tuple<int, int>> m_StavePV;
  // set of support structures
  std::set<G4LogicalVolume*> m_SupportLV;

  // setup parameters
  std::array<int, n_Layers> m_IsLayerActive{};
  std::array<int, n_Layers> m_IsLayerSupportActive{};
  std::array<int, n_Layers> m_IsBlackHole{};
  std::array<int, n_Layers> m_N_staves{};
  std::array<double, n_Layers> m_nominal_radius{};
  std::array<double, n_Layers> m_nominal_phitilt{};
  std::array<double, n_Layers> m_nominal_phi0{};

  // For modified geometry
  bool apply_misalignment {false};
  std::string m_misalignmentFile="";
  double m_GlobalDisplacementX = 0.0;
  double m_GlobalDisplacementY = 0.0;
  double m_GlobalDisplacementZ = 0.0;
};

#endif
