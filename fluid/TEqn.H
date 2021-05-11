
    fvScalarMatrix TEqn
    (
        fvm::div(phi, T)
      - fvm::laplacian(DT, T)
      //try to find how to input with turbulent diffusion rate
      //Seems, DT_lam+DT_turb, DT_turb = nu_turb/Prt (Prantl_number???)
      // LES {model eddyDiffusivity;  Prt 0.85;} 
    );
    TEqn.relax();
    TEqn.solve();
//    Info<< "    Temperature"<< T << endl; 
