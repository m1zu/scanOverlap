#include "Helpers.hh"
#include "coordinate.hh"

#include <TApplication.h>
#include <TVirtualFitter.h>
#include <TEllipse.h>

int main(int argc, char** argv) {
  TApplication application("analysis", &argc, argv);
  //TH1::AddDirectory(false);
  Helpers::setRootStyle();

  ///////////////////////// SHORT PIECE //////////////////////////////////

  QFile textFile("/home/iwanicki/sw/opticalCon/data/4TSAACFIM00387/scan/short.csv"); //TODO GET DATA AND SET PATH
  int count=0;
  if (textFile.open(QIODevice::ReadOnly)) {
      QTextStream stream(&textFile);
      while (!stream.atEnd())
      {
          count++;
          stream.readLine();
      }
  } else {
      qDebug() << "cannot open file !!";
      return 0;
  }
  textFile.close();

  const int nFibresShort = count;
  TGraphErrors* gs = new TGraphErrors(nFibresShort);
  count = 0;
  if (textFile.open(QIODevice::ReadOnly)) {
      QTextStream stream(&textFile);
      while (!stream.atEnd())
      {
          coordinate fibre;
          double temp;
          stream >> fibre.number >> temp
                    >> fibre.x >> fibre.y;
          qDebug() << "shortFiber" << fibre.number << fibre.x << fibre.y;
          if (fibre.number != (count+1))
              qDebug() << "fibre " << count << " skipped!";
          gs->SetPoint(fibre.number-1, (fibre.x*0.001), (fibre.y+4800.));
          gs->SetPointError(fibre.number-1, 0.125, 125);
          count++;
          stream.readLine();
      }
  }
  textFile.close();

  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->cd();
  gs->GetXaxis()->SetTitle("x [mm]");
  gs->GetYaxis()->SetTitle("y [#mum]");
  gs->GetXaxis()->SetTitleOffset(1.25);
  gs->GetXaxis()->SetTitleSize(25);
  gs->GetYaxis()->SetTitleOffset(1.15);
  gs->GetYaxis()->SetTitleSize(25);
  gs->SetMarkerColor(kBlack);
  gs->SetLineColor(14);
  gs->SetTitle("");
  //gs->GetYaxis()->SetRangeUser(8.,26.);
  //gs->GetXaxis()->SetLimits(0.,230.);
  gs->Draw("ape");

  /*
  TEllipse* el0 = new TEllipse();
  count = 0;
  if (textFile.open(QIODevice::ReadOnly)) {
      QTextStream stream(&textFile);
      while (!stream.atEnd())
      {
          coordinate fibre;
          double temp;
          stream >> fibre.number >> temp
                    >> fibre.x >> fibre.y;
          qDebug() << "shortFiber" << fibre.number << fibre.x << fibre.y;
          if (fibre.number != (count+1))
              qDebug() << "fibre " << count << " skipped!";
          el0->DrawEllipse( (fibre.x*0.001), (fibre.y+4800.), 0.125, 125, 0, 360, 180);
          count++;
          stream.readLine();
      }
  }
  textFile.close();
  */

    ///////////////////////// LONG PIECE //////////////////////////////////

  textFile.setFileName("/home/iwanicki/sw/opticalCon/data/4TSAACFIM00387/scan/long.csv");
  count=0;
  if (textFile.open(QIODevice::ReadOnly)) {
      QTextStream stream(&textFile);
      while (!stream.atEnd())
      {
          count++;
          stream.readLine();
      }
  } else {
      qDebug() << "cannot open file !!";
      return 0;
  }
  textFile.close();

  const int nFibresLong = count;
  TGraphErrors* gl = new TGraphErrors(nFibresLong);
  count = 0;
  if (textFile.open(QIODevice::ReadOnly)) {
      QTextStream stream(&textFile);
      while (!stream.atEnd())
      {
          coordinate fibre;
          double temp;
          stream >> fibre.number >> temp
                  >> fibre.x >> fibre.y;
          qDebug() << "longFiber" << fibre.number << fibre.x << fibre.y;
          if (fibre.number != (count+1))
              qDebug() << "fibre " << count << " skipped!";
          gl->SetPoint(fibre.number-1, -(fibre.x*0.001), (fibre.y+4800.));
          gl->SetPointError(fibre.number-1, 0.125, 125.);
          count++;
          stream.readLine();
      }
  }
  textFile.close();

  gl->SetMarkerStyle(kCircle);
  gl->SetMarkerColor (kBlue);
  gl->SetLineColor(kBlue);
  gl->Draw("pe same");

  /*
  TLegend* l1 = new TLegend(.8,.8,.9,.9);
  l1->AddEntry(gs ,"connection piece", "p");
  l1->AddEntry(gl ,"fiber mat ", "p");
  l1->Draw("SAME");
  */

  application.Run();
  return 0;
}
