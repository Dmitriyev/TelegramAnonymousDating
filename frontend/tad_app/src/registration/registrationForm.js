import React, {useState,setState} from 'react';
import './style.css'
function RegistrationForm() {
    
    const [Name, setName] = useState(null);
    const [Age, setAge] = useState(null);
    const [Gender, setGender] = useState(null);
    const [Orientation,setOrientation] = useState(null);
    const [City,setCity] = useState(null);
    const [Bio,setBio] = useState(null);

    function Dropdown() {
        const [isOpen, setIsOpen] = useState(false);
        const [selectedOption, setSelectedOption] = useState(null);
      
        const toggleDropdown = () => {
          setIsOpen(!isOpen);
        };
      
        const handleSelect = (option) => {
          setSelectedOption(option);
          setIsOpen(false); 
        };
    }
    const handleInputChange = (e) => {
        const {id , value} = e.target;
        if(id === "Name"){
            setName(value);
        }
        if(id === "Age"){
            setAge(value);
        }
        if(id === "Gender"){
            setGender(value);
        }
        if(id === "Orientation"){
            setOrientation(value);
        }
        if(id === "City"){
            setCity(value);
        }
        if(id === "Bio"){
            setBio(value);
        }

    }

    const handleSubmit  = () => {
        console.log(Name,Age,Gender,Orientation,City,Bio);
    }

    return(
            <div class="limiter">
                <div class="container-login100">
                    <div class="wrap-login100">
                        <form class="login100-form validate-form">
                            <span class="login100-form-title p-b-26">
                                Welcome
                            </span>
                            <span class="login100-form-title p-b-48">
                                <i class="zmdi zmdi-font"></i>
                            </span>
        
                            <div class="wrap-input100 validate-input" data-validate = "Valid Name is: abc">
                                <input class="input100" type="text" value={Name} name="Name"></input>
                                <span class="focus-input100" data-placeholder="Name"></span>
                            </div>
        
                            <div class="wrap-input100 validate-input" data-validate=">=0">
                                <span class="btn-show-pass">
                                    <i class="zmdi zmdi-eye"></i>
                                </span>
                                <input class="input100" type="number" value={Age} name="Age"></input>
                                <span class="focus-input100" data-placeholder="Age"></span>
                            </div>

                            <div class="wrap-input100 validate-input">
                                <span class="focus-input100"></span>
                                    <select class="input100" name='Gender' id="Gender" value={Gender} onChange={handleInputChange} required>
                                        <option value="Bi">Man</option>
                                        <option value="Gay">Woman</option>
                                        <option value="Hetero">DoubleSexual</option>
                                    </select>
                            </div>

                            <div class="wrap-input100 validate-input" data-validate = "Valid Name is: abc">
                                <span class="focus-input100"></span>
                                    <select class="input100" name='Orientation' id="Orintation" value={Orientation} onChange={handleInputChange} required>
                                        <option value="Bi">Bi</option>
                                        <option value="Gay">Gay</option>
                                        <option value="Hetero">Hetero</option>
                                    </select>
                            </div>

                            <div class="wrap-input100 validate-input">
                                <span class="focus-input100"></span>
                                    <select class="input100" name='City' id="City" value={City} onChange={handleInputChange} required>
                                        <option value="Bi">Moscow</option>
                                        <option value="Gay">New York</option>
                                        <option value="Hetero">Omsk</option>
                                    </select>
                            </div>

                            <div class="wrap-input100 validate-input">
                                <input class="input100" type="text" value={Bio} name="Bio"></input>
                                <span class="focus-input100" data-placeholder="Bio"></span>
                            </div>
        
                            <div class="container-login100-form-btn">
                                <div class="wrap-login100-form-btn">
                                    <div class="login100-form-bgbtn"></div>
                                    <button class="login100-form-btn">
                                        Start Search
                                    </button>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>
            </div>
    )       
}

export default RegistrationForm