import logo from "./logo.svg";
import "./App.css";
import Header from "./registration/header";
import RegistrationForm from "./registration/registrationForm";
import Menu from "./menu/menuForm";

import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Seacrh from "./search/search";

function App() {
  return (
    <div className="index">
    <Router>
      <Routes>
        <Route path="/edit_account" element={<RegistrationForm />}/>
        <Route path="/menu" element={<Menu />} />
        <Route path="/search" element={<Seacrh />} />
          {/* <Route path="contact" element={<Contact />} />
          <Route path="*" element={<NoPage />} /> */}
      </Routes>
    </Router>
      <Header />
      {/* <RegistrationForm /> */}
      </div>
  );
}

export default App;
