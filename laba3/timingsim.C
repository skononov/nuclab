#include <iostream>
#include <TH1F.h>
#include <TF1.h>
#include <TRandom3.h>

Double_t RC=10;  //time constant for anode circuit
Double_t tts=1;  //transition time spread of PMT
Double_t rise=0.5; //rise time of BC-420
Double_t decay=1.5; //decay time of BC-420
Double_t ampres=0.5; //single photoelectron amplitude resolution (limited gaussian)

TRandom3* rnd=new TRandom3();

TF1 *fsctime=new TF1("fsctime","(1-exp(-x/[0]))*exp(-x/[1])",0,100);

Double_t rnd_pulse(Double_t *x, Double_t *par)
{
    Double_t t=*x; //time

    Double_t mu=par[0]; //mean number of photoelectrons

    Double_t sum=0, a0, t0;

    Int_t N=rnd->Poisson(mu);
    for(Int_t i=0; i<N; i++) {
        while( (a0=rnd->Gaus(1,ampres)) < 0 ) {}

        t0=fsctime->GetRandom(0,100)+10+rnd->Gaus(0,tts);

        if( t>=t0 )
            sum+=a0*exp(-(t-t0)/RC);
    }

    return sum;
}

TF1 *fpulse=new TF1("fpulse",rnd_pulse,0,100,1);

#define CS(i) \
    ns[i]=rnd->Poisson(csecem);\
    for(k[i]=0; k[i]<ns[i]; k[i]++) {\
        dt[i]=rnd->Gaus(1,sigma);\

void timingsim(Int_t nev=100)
{
    fsctime->SetParameters(rise,decay);

    Double_t Npe=10;
    fpulse->SetParameter(0,Npe);
    fpulse->SetNpx(1000);

    Double_t csecem=3; //coef. of secondary emission
    Double_t sigma=0.1; //tts for single stage

    TH1F* hta=new TH1F("hta","time of electron arrival to anode",1000,0,50);
    TH1F* htma=new TH1F("htma","mean time of electron arrival to anode",100,10,20);
    TH1F* htsa=new TH1F("htsa","RMS time of electron arrival to anode",100,0,1);
    TH1F* ha=new TH1F("ha","amplitude at anode",100,0,1e8);

    Int_t k[14], ns[14];
    Double_t dt[14];

    for(Int_t i=0; i<nev; i++) {
        hta->Reset();
        Double_t dtpc=rnd->Gaus(1,sigma);
        UInt_t amp=0;
        CS(0)
        CS(1)
        CS(2)
        CS(3)
        CS(4)
        CS(5)
        CS(6)
        CS(7)
        CS(8)
        CS(9)
        CS(10)
        CS(11)
        CS(12)
        CS(13)
            amp++;
            Double_t ta=dtpc+dt[0]+dt[1]+dt[2]+dt[3]+dt[4]+
            dt[5]+dt[6]+dt[7]+dt[8]+dt[9]+dt[10]+dt[11]+dt[12]+dt[13];
            hta->Fill(ta);
        }}}}}}}}}}}}}}
        cout<<i+1<<endl;
        ha->Fill((double)amp);
        htma->Fill(hta->GetMean());
        htsa->Fill(hta->GetRMS());
    }
}