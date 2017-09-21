#ifndef DETECTORHISTOGRAM_H
#define DETECTORHISTOGRAM_H

// --- ROOT system ---
#include <TH1.h>
#include <TList.h>


class DetectorHistogram
{
public:

	enum Modules {kNhists = 5, kFirstModule = 1, kLastModule = 4};
	enum Mode {kSingleHist, kModules, kInterModules};
	DetectorHistogram():
		fHistogram123(0),
		fHistograms(),
		fInterModuleHistograms()
	{}

	DetectorHistogram(TH1 * hist, TList * owner, Mode = kInterModules);

	// Default copy constructor will do the job.
	// as we don't need two copies of the same hists

	// Don't delete anything as all histograms belong to the owner
	virtual ~DetectorHistogram() {}

	virtual void FillAll(Int_t sm1, Int_t sm2, Float_t x, Float_t y = 1.0);
	virtual void FillModules(Int_t sm1, Int_t sm2, Float_t x, Float_t y = 1.0);

	virtual void FillAll(Int_t sm1, Int_t sm2, Float_t x, Float_t y, Float_t);
	virtual void FillModules(Int_t sm1, Int_t sm2, Float_t x, Float_t y, Float_t);

	virtual TString Title(TString title, Int_t i) const;
	virtual TString Title(TString title, Int_t i, Int_t j) const;

protected:
	virtual Int_t Index(Int_t sm1, Int_t sm2) const;


private:
	DetectorHistogram(const DetectorHistogram &);

	TH1 * fHistogram123;                                       //! histogram for module 123
	TH1 * fHistograms[kNhists];                                //! Keep total + all modules
	TH1 * fInterModuleHistograms[kNhists * (kNhists + 1) / 2]; //! Number of cobinations of interdetector histograms
	Mode fMode;
};
#endif