    const fvMesh& mesh = fluidRegions[i];

//    rhoThermo& thermo = thermoFluid[i]; //just for boundary to calculate Kappa, maybe not needed

    volVectorField& U = UFluid[i];
    surfaceScalarField& phi = phiFluid[i];
    volScalarField& p = pFluid[i];
    volScalarField& T = TFluid[i];
    
    IOdictionary transportProperties
    (
       IOobject
       (
        "transportProperties",
        runTime.constant(),
        fluidRegions[i],
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
       )
    );    

	dimensionedScalar DT
	(
	    "DT",
	//    dimViscosity,
	    transportProperties.lookup("DT")
	);
/*
	dimensionedScalar nu
	(
	    "nu",
	//    dimViscosity,
	    transportProperties.lookup("nu")
	);    
*/	
	
//    dimensionedScalar DT("DT", transportProperties[i].lookup("DT"));
    
    
    singlePhaseTransportModel fluid(U, phi);
//    Info<< "THIS IS NU() " << fluid.nu() << "THIS IS NU()" << endl;
//    IOMRFZoneList& MRF = MRFfluid[i];
//    incompressible::momentumTransportModel& turb = turbulence[i];    
//    singlePhaseTransportModel& fluid = singlePhaseFluid[i];

//    Info<< "THIS IS NU() " << fluid.nu() << "THIS IS NU()" << endl;
//    singlePhase.correct();
//    singlePhasefluid[i].correct();
   

    fv::options& fvOptions = fluidFvOptions[i];

    const label pRefCell = pRefCellFluid[i];
    const scalar pRefValue = pRefValueFluid[i];

    bool& resReachedFluid = residualReachedFluid[i];
    bool& residualControlUsed = residualControlUsedFluid[i];
