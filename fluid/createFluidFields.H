// Initialise fluid field pointer lists

PtrList<rhoReactionThermo> thermoFluid(fluidRegions.size()); // JUST FOR BOUNDARY TO READ KAPPA

//PtrList<singlePhaseTransportModel> singlePhaseFluid(fluidRegions.size()); //include customized non-newtonian fluid model, need for U equation calculate visocisty.
//PtrList<incompressible::momentumTransportModel> turbulence(fluidRegions.size()); //turbulence model, no need to be used for current. Let's assume a laminar flow.

PtrList<volVectorField> UFluid(fluidRegions.size()); //velocity field, need for U and P equation
PtrList<surfaceScalarField> phiFluid(fluidRegions.size()); //flux, need for T and U field

PtrList<volScalarField> pFluid(fluidRegions.size()); //pressure, for P equ
PtrList<volScalarField> TFluid(fluidRegions.size()); //temperature, for T equ

List<label> pRefCellFluid(fluidRegions.size(), 0);
List<scalar> pRefValueFluid(fluidRegions.size(), 0.0); //along with pRefCell, fix a reference pressure if boundaries do not fix pressure level, periodic conditions for instance

List<bool> residualReachedFluid(fluidRegions.size(), true);
List<bool> residualControlUsedFluid(fluidRegions.size(), false);

PtrList<IOMRFZoneList> MRFfluid(fluidRegions.size());
PtrList<fv::options> fluidFvOptions(fluidRegions.size());

//PtrList<IOdictionary> transportProperties(fluidRegions.size());
PtrList<volScalarField> nu(fluidRegions.size()); //pressure, for P equ

// Populate fluid field pointer lists
forAll(fluidRegions, i)
{
    Info<< "*** Reading fluid mesh thermophysical properties for region "
        << fluidRegions[i].name() << nl << endl;

    Info<< "    Adding to thermoFluid\n" << endl;

    thermoFluid.set
    (
        i,
        rhoReactionThermo::New(fluidRegions[i]).ptr()
    );


    Info<< "    Adding to UFluid\n" << endl;
    UFluid.set
    (
        i,
        new volVectorField
        (
            IOobject
            (
                "U",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

    Info<< "    Adding to phiFluid\n" << endl;
    phiFluid.set
    (
        i,
        new surfaceScalarField
        (
            IOobject
            (
                "phi",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::READ_IF_PRESENT,
                IOobject::AUTO_WRITE
            ),
            fvc::flux(UFluid[i])
        )
    );

    Info<< "    Adding to TFluid\n" << endl;
    TFluid.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "T",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

/* shouldn't be added here!!!
// add non-newtonian transport model
    Info<< "    Adding to singlePhaseTransportModel\n" << endl;
    singlePhaseFluid.set
    (
        i,
        new singlePhaseTransportModel
        (
            UFluid[i],
            phiFluid[i]
        )
    );    
// add non-newtonian transport model
*/
/*
// add non-newtonian turbulence model
    Info<< "    Adding to singlePhaseTransportModel\n" << endl;
    turbulence.set
    (
        i,
        incompressible::momentumTransportModel::New
        (
          UFluid[i], 
          phiFluid[i],
          singlePhaseFluid[i]
        ).ptr()
    );    
// add non-newtonian turbulence model
*/

/*
    Info<< "    Adding to transportProperties\n" << endl;
    transportProperties.set
    (
        i,
	new IOdictionary
	(
	    IOobject
	    (
		"transportProperties",
		runTime.constant(),
		fluidRegions[i],
		IOobject::MUST_READ_IF_MODIFIED,
		IOobject::NO_WRITE
	    )
	)
     );
*/

// thermal diffusivity
//   DT[i] = dimensionedScalar("DT",dimLength, transportProperties[i].lookup("DT"));
// thermal diffusivity

    pFluid.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "p",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

//    singlePhaseTransportModel& fluid(UFluid[i], phiFluid[i]);
/*
    Info<< "    Adding to nu\n" << endl;
    nu.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "nu",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            fluid.nu()
        )
    );
*/
    
    const dictionary& simpleDict =
        fluidRegions[i].solutionDict().subDict("SIMPLE");



    setRefCell
    (
        pFluid[i],
        simpleDict,
        pRefCellFluid[i],
        pRefValueFluid[i]
    );
    
/*
    Info<< "    Adding MRF\n" << endl;
    MRFfluid.set
    (
        i,
        new IOMRFZoneList(fluidRegions[i])
    );
*/

    Info<< "    Adding fvOptions\n" << endl;
    fluidFvOptions.set
    (
        i,
        new fv::options(fluidRegions[i])
    );

//    turbulence[i].validate(); // don't know how it impact...
}
