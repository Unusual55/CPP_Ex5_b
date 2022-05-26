//#include "OrgChart.hpp"
//#include <iostream>
//
//using std::cout;
//using std::boolalpha;
//using ariel::OrgChart;
//
//int main() {OrgChart organization;
//    organization.add_root("CEO")
//            .add_sub("CEO", "CTO")    // Now the CTO is subordinate to the CEO
//            .add_sub("CEO", "CFO")    // Now the CFO is subordinate to the CEO
//            .add_sub("CEO", "COO")    // Now the COO is subordinate to the CEO
//            .add_sub("CTO", "VP_SW")  // Now the VP Software is subordinate to the CTO
//            .add_sub("COO", "VP_BI"); // Now the VP_BI is subordinate to the COO
//
//    //   cout << organization << endl; /* Prints the org chart in a reasonable format. For example:
//    //        CEO
//    //        |--------|--------|
//    //        CTO      CFO      COO
//    //        |                 |
//    //        VP_SW             VP_BI
//    //  */
//
//
//    organization.add_sub("VP_BI", "New Employee");
////    organization.add_sub("ME", "New Employee");
//    organization.add_root("ME");
//    organization.add_sub("ME", "New Employee");
//}
