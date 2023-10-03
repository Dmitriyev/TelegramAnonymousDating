import logo from "./logo.svg";
import "./App.css";
import Header from "./registration/header";
import RegistrationForm from "./registration/registrationForm";
import Menu from "./menu/menuForm";

import { BrowserRouter as Router, Routes, Route } from "react-router-dom";

function App() {
  return (
    <div className="App">
    <Router>
      <Routes>
        <Route path="/" element={<RegistrationForm />}/>
        <Route path="/menu" element={<Menu />} />
          {/* <Route path="blogs" element={<Blogs />} />
          <Route path="contact" element={<Contact />} />
          <Route path="*" element={<NoPage />} /> */}
      </Routes>
    </Router>
      <Header />
      {/* <RegistrationForm /> */}
      </div>
  );
}

export default App;
