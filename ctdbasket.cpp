#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

//Cheapest to Deliver Basket C++ Terminal Calcuator
//NO AI USED
//Credits GitHub RobertNikolasDaniel

//---GENERAL FUNCTIONS---

//Coupon Payment
double couponpay( double par, double rate, double freq ) {
	return ( par * rate ) / freq;
}

//Accrued Interest
double accint( double daysince, double daysin, double couponpay ) {
	return ( daysince / daysin ) * couponpay;
}

//Dirty Price
double dirty( double clean, double accint ) {
	return clean + accint;
}

//Projected Accrued Interest
double projaccint( double accint, double daydelivery, double daysin, double couponpay ) {
	return accint + ( ( daydelivery / daysin ) * couponpay );
}

//Repo Cost
double repocost( double dirty, double repo, double daydelivery ) {
	return dirty * repo * ( daydelivery / 360 );
}

//---FUTURE AND BASIS SPECIFIC FUNCTIONS---

//Converted Market Value Future Price
double mktfuturepricecf( double mktfutureprice, double cf ) {
	return mktfutureprice * cf;
}

//Market Value Invoice Price
double mktinvoice( double mktfuturepricecf, double projai ) {
	return mktfuturepricecf + projai;
}

//Market Value Gross Basis
double mktgrossbasis( double dirty, double mktfuturepricecf ) {
	return dirty - mktfuturepricecf;
}

//Market Value Net Basis
double mktnetbasis( double dirty, double mktinvoice ) {
	return dirty - mktinvoice;
}

//---MAIN---

int main() {
	//---WELCOME TEXT---
	std::cout << "\n---C++ Cheapest to Deliver Basket Basic Calculator---\n";
	std::cout << "\n!!!IMPORTANT";
	std::cout << "\nDECIMAL FORM: Repo, Coupon Rate, Conversion Factor";
	std::cout << "\n100 NOTIONAL FORM: Par, Clean Price\n";

	//---DEFINE VARIABLES---
	double mktfutureprice, daydelivery, basketsize;

	//---MARKET FUTURES INPUTS---
	std::cout << "\n---MARKET FUTURES INPUTS---\n" << std::endl;

	//Market Futures Price
	std::cout << "\nMarket Futures Price: ";
	std::cin >> mktfutureprice;

	//Days to Delivery
	std::cout << "\nDays To Delivery: ";
	std::cin >> daydelivery;

	//---SET CTD BASKET SIZE---
	std::cout << "\n";
	std::cout << "\n---CTD BASKET SIZE INPUT---\n" << std::endl;
	std::cout << "\nNumber Of Bonds In Delivery Basket: ";
	std::cin >> basketsize;

	//---CTD BASKET VECTOR---
	std::cout << "\n";
	std::cout << "\n---CTD BASKET INPUTS---\n" << std::endl;

	//Structure Types
	struct ctdbasket {
		std::string cusip;
		double repo;
		double cf;
		double dtd;
		double par;
		double clean;
		double rate;
		double freq;
		double since;
		double period;
		double payment;
		double ai;
		double dirty;
		double pjai;
		double repcost;
		double mktfut;
		double mktfutcf;
		double mktinvoice;
		double mktgross;
		double mktnet;
	};
	
	//Create Basket Vector
	std::vector<ctdbasket> bond;

	//Create Count Double
	int count;

	//Loop and Pushback Inputs
	for ( count = 0; count < basketsize; count++ ) {

		//temporary storage vector
		ctdbasket temp;

		//define intermediate variables for output math
		double vrepo, vcf, vpar, vclean, vrate, vfreq, vsince, vperiod;

		//---INPUTS---

		//cusip
		std::cout << "\nCUSIP For Bond " << count + 1 << ": ";
		std::cin >> temp.cusip;

		//repo
		std::cout << "\nRepo For Bond " << count + 1 << ": ";
		std::cin >> vrepo;
		temp.repo = vrepo;

		//cf
		std::cout << "\nCF For Bond " << count + 1 << ": ";
		std::cin >> vcf;
		temp.cf = vcf;

		//dtd
		temp.dtd = daydelivery;
		
		//par
		std::cout << "\nPar For Bond " << count + 1 << ": ";
		std::cin >> vpar;
		temp.par = vpar;

		//clean
		std::cout << "\nClean Price For Bond " << count + 1 << ": ";
		std::cin >> vclean;
		temp.clean = vclean;

		//rate
		std::cout << "\nCoupon Rate For Bond " << count + 1 << ": ";
		std::cin >> vrate;
		temp.rate = vrate;

		//freq
		std::cout << "\nCoupon Frequency For Bond " << count + 1 << ": ";
		std::cin >> vfreq;
		temp.freq = vfreq;

		//since
		std::cout << "\nDays Since Last Coupon For Bond " << count + 1 << ": ";
		std::cin >> vsince;
		temp.since = vsince;

		//period
		std::cout << "\nDays In Coupon Period For Bond " << count + 1 << ": ";
		std::cin >> vperiod;
		temp.period = vperiod;

		//---GENERAL OUTPUTS, DEFINE VARIABLES FOR MATH AND STORE---

		//coupon payment
		double vpay = couponpay( vpar, vrate, vfreq );
		temp.payment = vpay;

		//accrued interest
		double vaci = accint( vsince, vperiod, vpay );
		temp.ai = vaci;

		//dirty price
		double vdp = dirty( vclean, vaci );
		temp.dirty = vdp;

		//projected acrrued interest
		double vpai = projaccint( vaci, daydelivery, vperiod, vpay );
		temp.pjai = vpai;

		//repo cost
		double vrc = repocost( vdp, vrepo, daydelivery );
		temp.repcost = vrc;

		//---FUTURE AND BASIS OUTPUTS, DEFINE VARIABLES FOR MATH AND STORE---

		//market value future spot
		temp.mktfut = mktfutureprice;

		//market value converted future spot
		double mktfutecf = mktfuturepricecf( mktfutureprice, vcf );
		temp.mktfutcf = mktfutecf;

		//market value invoice price
		double mktiv = mktinvoice( mktfutecf, vpai );
		temp.mktinvoice = mktiv;

		//market value gross basis
		double mktgb = mktgrossbasis( vdp, mktfutecf );
		temp.mktgross = mktgb;

		//market value net basis
		double mktnb = mktnetbasis( vdp, mktiv );
		temp.mktnet = mktnb;
	
		//---PUSH TEMP VECTOR INTO CTD BASKET VECTOR---
		bond.push_back(temp);

		//end of bond text
		std::cout << "\n";
		std::cout << "\n--END OF BOND " << count + 1 << "---\n" << std::endl;
	}
		
	//---CTD BASKET INPUTS TABLE---
	std::cout << "\n---INPUTS TABLE---\n" << std::endl;

	//formatting
	std::cout << std::fixed << std::setprecision(6);

	//headers
	std::cout << std::left
		  << std::setw(14) << "CUSIP"
		  << std::right
		  << std::setw(14) << "REPO"
		  << std::setw(14) << "CF"
		  << std::setw(14) << "DTD"
   		  << std::setw(14) << "PAR"
		  << std::setw(14) << "CLEAN"
		  << std::setw(14) << "RATE"
                  << std::setw(14) << "FREQ"
		  << std::setw(14) << "SINCE"
		  << std::setw(14) << "PERIOD"
		  << "\n";

	//divider
	std::cout << std::string( 140, '-' ) << "\n";

	//for loop to generate body
	int q;
	for ( q = 0; q < bond.size(); q++ ) {
		std::cout << std::left
			  << std::setw(14) << bond[q].cusip
			  << std::right
			  << std::setw(14) << bond[q].repo
		          << std::setw(14) << bond[q].cf
			  << std::setw(14) << bond[q].dtd
			  << std::setw(14) << bond[q].par
			  << std::setw(14) << bond[q].clean
			  << std::setw(14) << bond[q].rate
			  << std::setw(14) << bond[q].freq
			  << std::setw(14) << bond[q].since
			  << std::setw(14) << bond[q].period
			  << "\n";
	}

	//bottom
	std::cout << std::string( 140, '-' ) << "\n";

	//---CTD BASKET FINANCING TABLE---
	std::cout << "\n" << std::endl;
	std::cout << "\n---FINANCING TABLE---\n" << std::endl;

	//header
	std::cout << std::left
		  << std::setw(14) << "CUSIP"
		  << std::right
		  << std::setw(14) << "PAYMENT"
		  << std::setw(14) << "ACC INT"
		  << std::setw(14) << "DIRTY"
		  << std::right
		  << std::setw(14) << "PROJ AI"
		  << std::setw(14) << "REP COST"
		  << "\n";

	//divider
	std::cout << std::string( 84, '-' ) << "\n";

	//for loop to generate body
	int p;
	for ( p = 0; p < bond.size(); p++ ) {
		std::cout << std::left
			  << std::setw(14) << bond[p].cusip
			  << std::right
			  << std::setw(14) << bond[p].payment
			  << std::setw(14) << bond[p].ai
			  << std::setw(14) << bond[p].dirty
			  << std::right
			  << std::setw(14) << bond[p].pjai
			  << std::setw(14) << bond[p].repcost
			  << "\n";
	}

	//bottom
	std::cout << std::string( 84, '-' ) << "\n";

	//---FUTURE AND BASIS TABLE---
	std::cout << "\n" << std::endl;
	std::cout << "\n---FUTURE AND BASIS TABLE---\n" << std::endl;

	//header
	std::cout << std::left
		  << std::setw(14) << "CUSIP"
		  << std::right
		  << std::setw(14) << "FUTURE"
		  << std::setw(14) << "CFUTURE"
		  << std::setw(14) << "INVOICE"
		  << std::setw(14) << "GROSS"
		  << std::setw(14) << "NET"
		  << "\n";

	//divider
	std::cout << std::string( 84, '-' ) << "\n";

	//for loop to generate body
	int z;
	for ( z = 0; z < bond.size(); z++ ) {
		std::cout << std::left
			  << std::setw(14) << bond[z].cusip
			  << std::right
			  << std::setw(14) << bond[z].mktfut
			  << std::setw(14) << bond[z].mktfutcf
			  << std::setw(14) << bond[z].mktinvoice
			  << std::setw(14) << bond[z].mktgross
			  << std::setw(14) << bond[z].mktnet
			  << "\n";
	}

	//bottom 
	std::cout << std::string( 84, '-' ) << "\n";

	//---FIND CHEAPEST TO DELIVER---
	double ctd = bond[0].mktnet;
	std::string rcusip = bond[0].cusip;
	int w;
	for ( w = 1; w < bond.size(); w++ ) {
		if ( ctd > bond[w].mktnet ) {
			ctd = bond[w].mktnet;
			rcusip = bond[w].cusip;
		}
	}

	//print the ctd and cusip
	std::cout << "\n" << std::endl;
	std::cout << "\n---CHEAPEST TO DELIVER SECURITY---\n" << std::endl;
	std::cout << "\nThe Cheapest To Deliver Is CUSIP: " << rcusip << "; With A Net Basis Of: " << ctd << ".\n" << std::endl;
	std::cout << "\n" << std::endl;
		
	//---RETURN ZERO--- 
	return 0;
}

