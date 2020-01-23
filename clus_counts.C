#include <vector>

#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TSystem.h"
#include "TLegend.h"

using std::vector;

void clus_counts(char* fin, char* fout, int min, int max) {
    TFile* file = new TFile(fin);
    TTreeReader reader("trees_DV_", file);

    TH1D* counts = new TH1D("count", "", 20, 0, 20);


    TTreeReaderValue<vector<double>> el1s(reader, "clus_l1ecal");
    TTreeReaderValue<vector<double>> el2s(reader, "clus_l2ecal");
    TTreeReaderValue<vector<double>> el3s(reader, "clus_l3ecal");
    TTreeReaderValue<vector<double>> el4s(reader, "clus_l4ecal");
    TTreeReaderValue<vector<double>> hl1s(reader, "clus_l1hcal");
    TTreeReaderValue<vector<double>> hl2s(reader, "clus_l2hcal");
    TTreeReaderValue<vector<double>> hl3s(reader, "clus_l3hcal");
    TTreeReaderValue<vector<double>> hl4s(reader, "clus_l4hcal");

    while (reader.Next()) {
        int ct = 0;
        for (auto i = 0; i < el1s->size(); i++) {
            double energy = el1s->at(i) + el2s->at(i) + el3s->at(i) + el4s->at(i) + hl1s->at(i) + hl2s->at(i) + hl3s->at(i) + hl4s->at(i);
            if (energy > min && energy < max) ct++;
        }
        counts->Fill(ct);
    }

    TCanvas* c = new TCanvas("c", "Cluster Counts", 2000, 1000);
    c->cd();

    counts->GetXaxis()->SetTitle("# of Clusters per Event");
    counts->SetLineColor(1);
    counts->Draw();

    c->Update();
    c->SaveAs(fout);
}

# ifndef __CINT__
int main(int argc, char** argv) {
    int min = (int) strtol(argv[3], NULL, 10);
    int max = (int) strtol(argv[4], NULL, 10);
    clus_counts(argv[1], argv[2], min, max);
}
# endif