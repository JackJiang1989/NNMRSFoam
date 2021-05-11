    // Momentum predictor

//    MRF.correctBoundaryVelocity(U);
//    U.component(1)=0;
//    U.component(2)=0;   
    tmp<fvVectorMatrix> tUEqn
    (
        fvm::div(phi, U)
//      + MRF.DDt(U)
//      + turb.divDevSigma(U)
        - fvm::laplacian(fluid.nu(), U)
//      - fvm::laplacian(nu, U)
     ==
        fvOptions(U)
    );
    fvVectorMatrix& UEqn = tUEqn.ref();

    UEqn.relax();

    fvOptions.constrain(UEqn);

    if (momentumPredictor)
    {
        solve(UEqn == -fvc::grad(p));

        fvOptions.correct(U);
    }
