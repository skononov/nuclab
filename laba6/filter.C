Double_t func(Double_t *x, Double_t *par)
{
    Double_t t=*x, Tr=par[0], Tf=par[1], kpz=par[2];

    if( t<0 ) return 0;

    Double_t Af=0.0;

    Double_t t1=0.0, t2=t;

    if( t-Tr>0 )
	t1=t-Tr;

    Af=(exp(-t1)-exp(-t2))/Tr;

    if( t-Tr-Tf<0 ) return Af;

    t1=0;
    t2=t-Tr-Tf;

    if( t-2*Tr-Tf>0 )
	t1=t-2*Tr-Tf;

    Af-=kpz*(exp(-t1)-exp(-t2))/Tr;

    return Af;
}

void filter(Double_t Tr=0.2, Double_t Tf=0.1, Double_t kpz=1)
{
    TF1* f=new TF1("f",func,-0.5,5,3);

    f->SetParameters(Tr,Tf,kpz);
    f->SetNpx(1000);

    f->Draw();
}