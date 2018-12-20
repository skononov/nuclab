Double_t z_vs_t(Double_t *x, Double_t *par)
{
    Double_t T=*x;
    Int_t N=int(T)+1;
    return 1.1*(0.5-(-1)**N*(T-N+0.5))-0.05;
}

void test()
{
    TCanvas *c1=new TCanvas("c1","c1",700,500);
    c1->Clear();
    c1->Range(-1,-0.2,5,1.2);

    TF1* fzt=new TF1("fzt",z_vs_t,0,4,0);
    fzt->SetNpx(1000);
    fzt->SetLineColor(kBlack);

    TGaxis *Xax=new TGaxis(-0.5.,0.,4.5,0.,-0.5,4.7,6,"+-U");

    TGaxis *Yax=new TGaxis(-0.2,-0.1,-0.2,1.15,-0.1,1.15,0,"");

    TLine *l1=new TLine(-0.2,1,4,1);
    l1->SetLineStyle(7);
    TLine *l2=new TLine(-0.2,-0.05,4,-0.05);
    l2->SetLineStyle(7);

    gStyle->SetTextFont(132);
    gStyle->SetTextSize(0.035);

    TLatex *tx0=new TLatex(0,-0.1,"T_{0}");
    TLatex *tx1=new TLatex(0.99,-0.1,"T_{0}+T_{per}");
    TLatex *tx2=new TLatex(1.98,-0.1,"T_{0}+2T_{per}");
    TLatex *tx3=new TLatex(2.94,-0.1,"T_{0}+3T_{per}");
    TLatex *tx4=new TLatex(3.9,-0.1,"T_{0}+4T_{per}");
    TLatex *ty1=new TLatex(-0.3,1,"L_{tube}");
    ty1->SetTextAlign(32);
    TLatex *ty2=new TLatex(-0.3,-0.05,"-L_{conn}/2");
    ty2->SetTextAlign(32);

    TLatex *ttx=new TLatex(4.5,-0.05,"T");
    ttx->SetTextFont(22);
    ttx->SetTextSize(0.045);
    TLatex *tty=new TLatex(-0.3,1.13,"Z");
    tty->SetTextFont(22);
    tty->SetTextSize(0.045);

    Xax->Draw();
    Yax->Draw();
    l1->Draw();
    l2->Draw();
    tx0->Draw();
    tx1->Draw();
    tx2->Draw();
    tx3->Draw();
    tx4->Draw();
    ty1->Draw();
    ty2->Draw();
    ttx->Draw();
    tty->Draw();

    fzt->Draw("same");
}