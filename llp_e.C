#include <vector>

#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TSystem.h"

using std::vector;

void llp_e(char* fin, char* fout) {
    TFile* file = new TFile(fin);
    TTreeReader reader("trees_DV_", file);

    TH1D* energy = new TH1D("energy", "LLP Energy", 1000, 0, 1000000);

    TTreeReaderValue<vector<double>> llp_e(reader, "llp_e");

    while (reader.Next()) {
        energy->Fill(llp_e->at(0));
        energy->Fill(llp_e->at(1));
    }

    TCanvas* c = new TCanvas("Canvas");
    c->cd();

    energy->GetXaxis()->SetTitle("Energy (MeV)");
    energy->Draw();

    c->Update();
    c->SaveAs(fout);
}

# ifndef __CINT__
int main(int argc, char** argv) {
    llp_e(argv[1], argv[2]);
}
# endif