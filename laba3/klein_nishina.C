
//d sigma / d cost (cost; Eg[MeV])
Double_t kn_diff_cs(Double_t *x, Double_t *par)
{
    static const Double_t re=2.8179402895e-13; //cm
    static const Double_t s0=TMath::Pi()*re*re;
    static const Double_t me=0.510998910; //MeV/c^2
    Double_t cost=*x;
    Double_t eps=par[0]/me; // Eg(MeV)/me

    Double_t P=1/(1+eps*(1-cost));
    return s0*P*P*(P+1/P-1+cost*cost);
}

TF1 *fdiffcs=new TF1("fdiffcs",kn_diff_cs,-1.,1.,1);

//d sigma / d Ee (Ee[MeV]; Eg[MeV])
Double_t kn_diff_cs_e(Double_t *x, Double_t *par)
{
    const Double_t me=0.510998910; //MeV/c^2
    Double_t Ee=*x; //MeV
    Double_t Eg=par[0]; //MeV
    Double_t Ee_max=Eg*(1-1/(1+2*(Eg/me)));
    if( Ee>=Ee_max ) return 0;

    Double_t cost=1-(1/(Eg-Ee)-1/Eg)*me;

    return kn_diff_cs(&cost,&Eg)*me/(Eg-Ee)**2;
}

TF1 *fdiffcse=new TF1("fdiffcse",kn_diff_cs_e,0,10,1);

//sigma(E[MeV])
Double_t kn_total_cs_e(Double_t *x, Double_t *par)
{
    static const Double_t re=2.8179402895e-13; //cm
    static const Double_t s0=2*TMath::Pi()*re*re;
    static const Double_t me=0.510998910; //MeV/c^2
    Double_t eps=*x/me;
    Double_t a=1+2*eps;
    return s0*( (1+eps)/eps/eps*(1+1/a-log(a)/eps) + log(a)/2/eps - (1+3*eps)/a/a );
}

//sigma_abs(E[MeV])
Double_t kn_total_cs_e_abs(Double_t *x, Double_t *par)
{
    Double_t Eg=*x, eps=Eg/0.511;
    Double_t Ee_max=Eg*(1-1/(1+2*eps));

    fdiffcse->SetParameter(0,Eg);
    return fdiffcse->Mean(0.,Ee_max)/Eg*fdiffcse->Integral(0.,Ee_max);
}

//sigma_sc(E[MeV])
Double_t kn_total_cs_e_sc(Double_t *x, Double_t *par)
{
    Double_t Eg=*x, eps=Eg/0.511;
    Double_t Ee_max=Eg*(1-1/(1+2*eps));

    fdiffcse->SetParameter(0,Eg);
    return (1-fdiffcse->Mean(0.,Ee_max)/Eg)*fdiffcse->Integral(0.,Ee_max);
}


TF1 *fcs=new TF1("fcs",kn_total_cs_e,0.01,100.,0);
TF1 *fcsabs=new TF1("fcsabs",kn_total_cs_e_abs,0.01,100.,0);
TF1 *fcssc=new TF1("fcssc",kn_total_cs_e_sc,0.01,100.,0);
