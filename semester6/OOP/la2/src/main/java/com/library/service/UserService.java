package com.library.service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Set;

import com.library.converter.UserConverter;
import com.library.dto.UserDTO;
import com.library.entity.User;
import com.library.repository.BookRepository;
import com.library.repository.UserRepository;

import org.keycloak.KeycloakPrincipal;
import org.keycloak.KeycloakSecurityContext;
import org.keycloak.representations.AccessToken;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Service;

@Service
public class UserService {
    private UserRepository userRepo;

    @Autowired
    public UserService(UserRepository repo) {
        this.userRepo = repo;
    }

    public Optional<User> findById(long id) {
        return userRepo.findById(id);
    }

    public List<User> findByLogin(String login) {
        return userRepo.findByLogin(login);
    }

    public UserDTO getUserDto(String Authorization) {
        UserDTO userDTO = new UserDTO();
        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        if (authentication != null) {
            if (authentication.getPrincipal() instanceof KeycloakPrincipal) {
                KeycloakPrincipal<KeycloakSecurityContext> kp = (KeycloakPrincipal<KeycloakSecurityContext>) authentication
                        .getPrincipal();

                AccessToken accessToken = kp.getKeycloakSecurityContext().getToken();
                Set<String> roles = accessToken.getResourceAccess().get("springboot-microservice").getRoles();
                Optional<String> optionalRole = roles.stream().findFirst();
                optionalRole.ifPresent(userDTO::setRole);
                userDTO.setSurname(accessToken.getFamilyName());
                userDTO.setName(accessToken.getGivenName());
                userDTO.setLogin(accessToken.getPreferredUsername());
            }
        }
        return userDTO;
    }

    public List<UserDTO> getAllUsers() {
        List<User> users = userRepo.findAll();
        List<UserDTO> answer = new ArrayList<>();
        for (User user : users) {
            answer.add(UserConverter.toDTO(user));
        }
        return answer;
    }

    public void returnBook(int id_user, int id_book) {

    }
}
