//it's compressible continuity errors, try to change to imcompressible code
//continuity, shouldn't be divergence of mass flux in the domain compare with ZERO?
//1. check how simple/piso make the continuity errors.
//2. check online to understand more.

{
    dimensionedScalar totalMass = fvc::domainIntegrate(rho);

    scalar sumLocalContErr =
    (
        fvc::domainIntegrate(mag(rho - thermo.rho()))/totalMass
    ).value();

    scalar globalContErr =
    (
        fvc::domainIntegrate(rho - thermo.rho())/totalMass
    ).value();

    cumulativeContErr[i] += globalContErr;

    Info<< "time step continuity errors (" << mesh.name() << ")"
        << ": sum local = " << sumLocalContErr
        << ", global = " << globalContErr
        << ", cumulative = " << cumulativeContErr[i]
        << endl;
}
